cmake_minimum_required(VERSION 3.16)
project(Lodestar)

set(CMAKE_CXX_STANDARD 11)

#SET(GCC_COVERAGE_COMPILE_FLAGS "--coverage")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -fPIC")

# Force use of MPL2 compatible licenses only.
add_compile_definitions(EIGEN_MPL2_ONLY)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
#include("${CMAKE_SOURCE_DIR}/cmake/modules/FindProtobuf.cmake")

option(WITH_GINAC "Use GiNaC" ON)
option(WITH_PROTOBUF "Use Protocol Buffers" OFF)
option(WITH_NNG "Use NNG" ON)
option(MAKE_STATIC_LIB "Make static library" ON)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("dep")
include_directories("tests")
include_directories("dep/nanopb")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")
#find_package(ginac REQUIRED 1.7.0)

remove_definitions(LS_USE_GINAC)

if (WITH_GINAC)
    add_compile_definitions(LS_USE_GINAC)

    # Find GiNaC
    find_path(GINAC_INCLUDE_DIR ginac/ginac.h /usr/local/include /usr/include)
    find_library(GINAC_LIBRARY ginac /usr/local/lib /usr/lib)

    # Find CLN
    find_path(CLN_INCLUDE_DIR cln/real.h /usr/local/include /usr/include)
    find_library(CLN_LIBRARY cln /usr/local/lib /usr/lib)

    if (GINAC_INCLUDE_DIR AND GINAC_LIBRARY)
        message("Found GiNaC.")
    else (GINAC_INCLUDE_DIR AND GINAC_LIBRARY)
        message(SEND_ERROR "Missing GiNaC library")
    endif (GINAC_INCLUDE_DIR AND GINAC_LIBRARY)

    if (CLN_INCLUDE_DIR AND CLN_LIBRARY)
        message("Found CLN.")
    else (CLN_INCLUDE_DIR AND CLN_LIBRARY)
        message(SEND_ERROR "Missing CLN library")
    endif (CLN_INCLUDE_DIR AND CLN_LIBRARY)

    message("Building with GiNaC and CLN.")
    include_directories(${GINAC_INCLUDE_DIR} ${CLN_INCLUDE_DIR})
endif ()

if (WITH_PROTOBUF)
    MESSAGE("Building with Protocol Buffers.")
    add_compile_definitions(LS_USE_PROTOBUF)

    # Find Protobuf
    find_package(Protobuf REQUIRED)
    include_directories(${Protobuf_INCLUDE_DIRS})

    #    FindProtobuf("${PROJECT_SOURCE_DIR}/Lodestar/io/proto")

    #    file(GLOB PROTOBUF_DEFINITION_FILES "*.proto")
    #    set(PROTOBUF_INPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/io/proto")
    #    set(PROTOBUF_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/io/proto")
    #    foreach(file ${PROTOBUF_DEFINITION_FILES})
    #        set(PROTOBUF_ARGUMENTS "protoc –proto_path=\"${PROTOBUF_INPUT_DIRECTORY}\" –cpp_out=\"${PROTOBUF_OUTPUT_DIRECTORY}\" \"${file}\"")
    #        execute_process(COMMAND ${PROTOBUF_OUTPUT_DIRECTORY}
    #                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    #                RESULT_VARIABLE PROTOBUF_RESULT
    #                OUTPUT_VARIABLE PROTOBUF_OUTPUT_VARIABLE)
    #    endforeach()

    file(GLOB PROTOBUF_INCLUDES "Lodestar/io/proto/*.pb.cc" "Lodestar/io/proto/*.hpp")
else ()
    UNSET(PROTOBUF_INCLUDES)
endif ()

if (WITH_NNG)
    find_library(NNG_LIBRARY nng)

    if (NOT NNG_LIBRARY)
        message(FATAL_ERROR "NNG was not found.")
    endif ()

    add_compile_definitions(LS_USE_NNG)
    MESSAGE("Building with NNG.")
endif ()

# Nanopb glob include

file(GLOB PROTOBUF_INCLUDES "Lodestar/io/proto/nano/*.pb.c" "Lodestar/io/proto/nano/*.pb.h")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    MESSAGE("Building in debug mode.")

    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.1)

    FetchContent_MakeAvailable(Catch2)
endif ()

add_executable(Lodestar Lodestar/primitives/Integrator.hpp Lodestar/primitives/integrators/IntegratorNewton.hpp Lodestar/analysis/BilinearTransformation.cpp Lodestar/analysis/BilinearTransformation.hpp Lodestar/systems/SystemStateless.hpp Lodestar/systems/StateSpace.cpp Lodestar/systems/StateSpace.hpp Lodestar/analysis/ZeroOrderHold.cpp Lodestar/analysis/ZeroOrderHold.hpp Lodestar/analysis/LinearSystemInverse.cpp Lodestar/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.cpp Lodestar/systems/TransferFunction.cpp Lodestar/systems/TransferFunction.hpp Lodestar/LodestarErrors.hpp Lodestar/LodestarErrorNames.hpp Lodestar/io/EigenProtoIface.cpp Lodestar/io/EigenProtoIface.hpp Lodestar/io/ProtoIfaceABC.hpp Lodestar/aux/UnitLiterals.hpp Lodestar/systems/DiscreteStateSpace.cpp Lodestar/systems/DiscreteStateSpace.hpp Lodestar/systems/DiscreteSystem.cpp Lodestar/systems/DiscreteSystem.hpp Lodestar/io/ProtoWrapper.cpp Lodestar/io/ProtoWrapper.hpp Lodestar/control/FixedGain.cpp Lodestar/control/FixedGain.hpp Lodestar/io/ProtoTypeTrait.hpp Lodestar/systems/SystemStateful.hpp Lodestar/symbolic/OrdinaryDifferentialEquation.cpp Lodestar/symbolic/OrdinaryDifferentialEquation.hpp Lodestar/control/DiscreteLQR.cpp Lodestar/control/DiscreteLQR.hpp Lodestar/synthesis/AlgebraicRiccatiEquation.cpp Lodestar/synthesis/AlgebraicRiccatiEquation.hpp Lodestar/filter/DiscreteLQE.cpp Lodestar/filter/DiscreteLQE.hpp Lodestar/io/GiNaCProtoIface.cpp Lodestar/io/GiNaCProtoIface.hpp ${PROTOBUF_INCLUDES} dep/nanopb/pb_common.c dep/nanopb/pb_common.h dep/nanopb/pb.h dep/nanopb/pb_decode.c dep/nanopb/pb_decode.h dep/nanopb/pb_encode.c dep/nanopb/pb_encode.h Lodestar/aux/CompileTimeQualifiers.hpp tests/TestMain.cpp tests/systems/StateSpace_test.cpp tests/primitives/integrators/IntegratorNewton_test.cpp tests/systems/TransferFunction_test.cpp tests/catchOnce.hpp Lodestar/aux/Conjunction.hpp Lodestar/aux/RecursionException.hpp tests/TestAuxFunctions.hpp Lodestar/aux/Repeat.hpp Lodestar/aux/Indices.hpp Lodestar/aux/AlgebraicOperators.hpp Lodestar/aux/OperationTypes.hpp Lodestar/aux/BinOpCheck.hpp Lodestar/aux/PairUp.hpp Lodestar/aux/TypeName.hpp Lodestar/aux/Pack.hpp Lodestar/time/Metronome.hpp Lodestar/time/TimeResolution.hpp tests/time/Metronome_test.cpp Lodestar/time/TimeDuration.hpp Lodestar/io/nng/Publisher.cpp Lodestar/io/nng/Publisher.hpp tests/io/proto/nano/Nanopb_test.cpp Lodestar/io/proto/nano/NanopbWrapper.hpp Lodestar/filter/SimpleMovingAverage.hpp Lodestar/aux/ArrayStack.hpp tests/aux/ArrayStack_test.cpp tests/filter/SimpleMovingAverage_test.cpp Lodestar/core/StatusOr.hpp Lodestar/core/Status.hpp tests/core/Status_test.cpp Lodestar/core/Status.cpp Lodestar/data/FastFourierTransform.cpp Lodestar/data/FastFourierTransform.hpp tests/data/FastFourierTransform_test.cpp Lodestar/primitives/differentiators/BackwardDifference.hpp tests/primitives/differentiators/BackwardDifference_test.cpp Lodestar/primitives/integrators/BogackiShampine.hpp Lodestar/primitives/integrators/ButcherTableau.hpp tests/primitives/integrators/ButcherTableau_test.cpp tests/primitives/integrators/BogackiShampine_test.cpp Lodestar/primitives/integrators/RungeKuttaFehlberg45.hpp tests/primitives/integrators/RungeKuttaFehlberg45_test.cpp Lodestar/primitives/integrators/RungeKuttaFehlberg78.hpp tests/primitives/integrators/RungeKuttaFehlberg78_test.cpp Lodestar/control/SampledPID.cpp Lodestar/control/SampledPID.hpp Lodestar/primitives/differentiators/AdaptiveBackwardDifference.hpp tests/primitives/differentiators/AdaptiveBackwardDifference_test.cpp Lodestar/primitives/sets/SetExpression.hpp Lodestar/primitives/sets/SetUnion.hpp Lodestar/primitives/sets/Singleton.hpp Lodestar/primitives/sets/SetEnum.hpp tests/primitives/sets/Sets_test.cpp Lodestar/primitives/sets/EmptySet.hpp Lodestar/primitives/sets/SetComplement.hpp Lodestar/symbolic/SymbolicFunctions.cpp Lodestar/symbolic/SymbolicFunctions.hpp Lodestar/filter/ContinuousSampledEKF.cpp Lodestar/filter/ContinuousSampledEKF.hpp tests/filter/ContinuousSampledEKF_test.cpp Lodestar/primitives/integrators/IntegratorsEnum.hpp tests/symbolic/OrdinaryDifferentialEquation_test.cpp tests/filter/CartPoleAuxFunctions.hpp Lodestar/control/ModelPredictiveControl.cpp Lodestar/control/ModelPredictiveControl.hpp Lodestar/GlobalConstants.hpp Lodestar/blocks/SignalBase.cpp Lodestar/blocks/SignalBase.hpp Lodestar/blocks/BlockProto.cpp Lodestar/blocks/BlockProto.hpp Lodestar/aux/DynamicDataTypes.hpp Lodestar/aux/Any.hpp Lodestar/aux/DynamicData.hpp Lodestar/aux/TemplateTraits.hpp Lodestar/blocks/Signal.cpp Lodestar/blocks/Signal.hpp Lodestar/aux/TemplateTools.hpp Lodestar/blocks/Block.cpp Lodestar/blocks/Block.hpp Lodestar/blocks/BlockBase.hpp Lodestar/blocks/BlockUtilities.hpp Lodestar/blocks/std/ConstantBlock.cpp Lodestar/blocks/std/ConstantBlock.hpp Lodestar/blocks/std/GainBlock.cpp Lodestar/blocks/std/GainBlock.hpp Lodestar/blocks/std/SignumBlock.cpp Lodestar/blocks/std/SignumBlock.hpp Lodestar/blocks/std/SumBlock.cpp Lodestar/blocks/std/SumBlock.hpp Lodestar/blocks/std/FunctionBlock.cpp Lodestar/blocks/std/FunctionBlock.hpp tests/blocks/Signal_test.cpp tests/aux/Any_test.cpp tests/aux/DynamicData_test.cpp tests/blocks/Block_test.cpp tests/blocks/SumBlock_test.cpp tests/blocks/GainBlock_test.cpp tests/blocks/SignumBlock_test.cpp tests/blocks/FunctionBlock_test.cpp tests/blocks/Blocks_test.cpp tests/blocks/ConstantBlock_test.cpp Lodestar/aux/DynamicDataTypes.cpp Lodestar/blocks/std/ConverterBlock.cpp Lodestar/blocks/std/ConverterBlock.hpp tests/blocks/ConverterBlock_test.cpp Lodestar/blocks/std/MuxBlock.cpp Lodestar/blocks/std/MuxBlock.hpp tests/blocks/MuxBlock_test.cpp Lodestar/blocks/std/DemuxBlock.cpp Lodestar/blocks/std/DemuxBlock.hpp tests/blocks/DemuxBlock_test.cpp Lodestar/blocks/std/ReImToComplexBlock.cpp Lodestar/blocks/std/ReImToComplexBlock.hpp tests/blocks/ReImToComplexBlock_test.cpp Lodestar/blocks/std/SaturationBlock.cpp Lodestar/blocks/std/SaturationBlock.hpp tests/blocks/SaturationBlock_test.cpp Lodestar/blocks/std/SwitchBlock.cpp Lodestar/blocks/std/SwitchBlock.hpp tests/blocks/SwitchBlock_test.cpp Lodestar/blocks/std/geometry/QuaternionBlock.cpp Lodestar/blocks/std/geometry/QuaternionBlock.hpp tests/blocks/geometry/QuaternionBlock_test.cpp Lodestar/blocks/BlockType.hpp Lodestar/blocks/BlockTraits.cpp Lodestar/blocks/BlockTraits.hpp tests/blocks/BlockTraits_test.cpp Lodestar/blocks/aux/DirectedGraph.cpp Lodestar/blocks/aux/DirectedGraph.hpp Lodestar/blocks/aux/StronglyConnectedComponents.cpp Lodestar/blocks/aux/StronglyConnectedComponents.hpp tests/blocks/aux/StronglyConnectedComponents_test.cpp Lodestar/blocks/BlockPack.cpp Lodestar/blocks/BlockPack.hpp tests/blocks/BlockPack_test.cpp tests/blocks/aux/DirectGraph_test.cpp Lodestar/blocks/aux/Executor.cpp Lodestar/blocks/aux/Executor.hpp tests/blocks/aux/Executor_test.cpp Lodestar/aux/DemangledType.cpp Lodestar/aux/DemangledType.hpp tests/aux/TemplateTraits_test.cpp Lodestar/blocks/std/systems/DiscreteStateSpaceBlock.cpp Lodestar/blocks/std/systems/DiscreteStateSpaceBlock.hpp tests/blocks/systems/DiscreteStateSpaceBlock_test.cpp Lodestar/aux/FunctionTraits.hpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(Lodestar Catch2::Catch2)
endif ()

if (WITH_PROTOBUF)
    target_link_libraries(Lodestar ${Protobuf_LIBRARIES})
endif ()

if (WITH_GINAC)
    target_link_libraries(Lodestar ${GINAC_LIBRARY})
    target_link_libraries(Lodestar ${CLN_LIBRARY})
endif ()

if (WITH_NNG)
    target_link_libraries(Lodestar nng pthread)
endif ()

if (MAKE_STATIC_LIB)
    add_library(liblodestar STATIC Lodestar/primitives/Integrator.hpp
            Lodestar/primitives/integrators/IntegratorNewton.hpp
            Lodestar/analysis/BilinearTransformation.cpp
            Lodestar/analysis/BilinearTransformation.hpp
            Lodestar/systems/SystemStateless.hpp
            Lodestar/systems/StateSpace.cpp
            Lodestar/systems/StateSpace.hpp
            Lodestar/analysis/ZeroOrderHold.cpp
            Lodestar/analysis/ZeroOrderHold.hpp
            Lodestar/analysis/LinearSystemInverse.cpp
            Lodestar/analysis/LinearSystemInverse.hpp
            Lodestar/systems/TransferFunction.cpp
            Lodestar/systems/TransferFunction.hpp
            Lodestar/LodestarErrors.hpp
            Lodestar/LodestarErrorNames.hpp
            Lodestar/io/EigenProtoIface.cpp
            Lodestar/io/EigenProtoIface.hpp
            Lodestar/io/ProtoIfaceABC.hpp
            Lodestar/aux/UnitLiterals.hpp
            Lodestar/systems/DiscreteStateSpace.cpp
            Lodestar/systems/DiscreteStateSpace.hpp
            Lodestar/systems/DiscreteSystem.cpp
            Lodestar/systems/DiscreteSystem.hpp
            Lodestar/io/ProtoWrapper.cpp
            Lodestar/io/ProtoWrapper.hpp
            Lodestar/control/FixedGain.cpp
            Lodestar/control/FixedGain.hpp
            Lodestar/io/ProtoTypeTrait.hpp
            Lodestar/systems/SystemStateful.hpp
            Lodestar/symbolic/OrdinaryDifferentialEquation.cpp
            Lodestar/symbolic/OrdinaryDifferentialEquation.hpp
            Lodestar/control/DiscreteLQR.cpp
            Lodestar/control/DiscreteLQR.hpp
            Lodestar/synthesis/AlgebraicRiccatiEquation.cpp
            Lodestar/synthesis/AlgebraicRiccatiEquation.hpp
            Lodestar/filter/DiscreteLQE.cpp
            Lodestar/filter/DiscreteLQE.hpp
            Lodestar/io/GiNaCProtoIface.cpp
            Lodestar/io/GiNaCProtoIface.hpp
#            ${PROTOBUF_INCLUDES}
#            dep/nanopb/pb_common.c
#            dep/nanopb/pb_common.h
#            dep/nanopb/pb.h
#            dep/nanopb/pb_decode.c
#            dep/nanopb/pb_decode.h
#            dep/nanopb/pb_encode.c
#            dep/nanopb/pb_encode.h
            Lodestar/aux/CompileTimeQualifiers.hpp
            Lodestar/aux/Conjunction.hpp
            Lodestar/aux/RecursionException.hpp
            Lodestar/aux/Repeat.hpp
            Lodestar/aux/Indices.hpp
            Lodestar/aux/AlgebraicOperators.hpp
            Lodestar/aux/OperationTypes.hpp
            Lodestar/aux/BinOpCheck.hpp
            Lodestar/aux/PairUp.hpp
            Lodestar/aux/TypeName.hpp
            Lodestar/aux/Pack.hpp
            Lodestar/time/Metronome.hpp
            Lodestar/time/TimeResolution.hpp
            Lodestar/time/TimeDuration.hpp
            Lodestar/io/nng/Publisher.cpp
            Lodestar/io/nng/Publisher.hpp
            Lodestar/io/proto/nano/NanopbWrapper.hpp
            Lodestar/filter/SimpleMovingAverage.hpp
            Lodestar/aux/ArrayStack.hpp
            Lodestar/core/StatusOr.hpp
            Lodestar/core/Status.hpp
            Lodestar/core/Status.cpp
            Lodestar/data/FastFourierTransform.cpp
            Lodestar/data/FastFourierTransform.hpp
            Lodestar/primitives/differentiators/BackwardDifference.hpp
            Lodestar/primitives/integrators/BogackiShampine.hpp
            Lodestar/primitives/integrators/ButcherTableau.hpp
            Lodestar/primitives/integrators/RungeKuttaFehlberg45.hpp
            Lodestar/primitives/integrators/RungeKuttaFehlberg78.hpp
            Lodestar/control/SampledPID.cpp
            Lodestar/control/SampledPID.hpp
            Lodestar/primitives/differentiators/AdaptiveBackwardDifference.hpp
            Lodestar/primitives/sets/SetExpression.hpp
            Lodestar/primitives/sets/SetUnion.hpp
            Lodestar/primitives/sets/Singleton.hpp
            Lodestar/primitives/sets/SetEnum.hpp
            Lodestar/primitives/sets/EmptySet.hpp
            Lodestar/primitives/sets/SetComplement.hpp
            Lodestar/symbolic/SymbolicFunctions.cpp
            Lodestar/symbolic/SymbolicFunctions.hpp
            Lodestar/filter/ContinuousSampledEKF.cpp
            Lodestar/filter/ContinuousSampledEKF.hpp Lodestar/control/ModelPredictiveControl.cpp Lodestar/control/ModelPredictiveControl.hpp Lodestar/GlobalConstants.hpp Lodestar/blocks/SignalBase.cpp Lodestar/blocks/SignalBase.hpp Lodestar/blocks/BlockProto.cpp Lodestar/blocks/BlockProto.hpp Lodestar/aux/DynamicDataTypes.hpp Lodestar/aux/Any.hpp Lodestar/aux/DynamicData.hpp Lodestar/aux/TemplateTraits.hpp Lodestar/blocks/Signal.cpp Lodestar/blocks/Signal.hpp Lodestar/aux/TemplateTools.hpp Lodestar/blocks/Block.cpp Lodestar/blocks/Block.hpp Lodestar/blocks/BlockBase.hpp Lodestar/blocks/BlockUtilities.hpp Lodestar/blocks/std/ConstantBlock.cpp Lodestar/blocks/std/ConstantBlock.hpp Lodestar/blocks/std/GainBlock.cpp Lodestar/blocks/std/GainBlock.hpp Lodestar/blocks/std/SignumBlock.cpp Lodestar/blocks/std/SignumBlock.hpp Lodestar/blocks/std/SumBlock.cpp Lodestar/blocks/std/SumBlock.hpp Lodestar/blocks/std/FunctionBlock.cpp Lodestar/blocks/std/FunctionBlock.hpp Lodestar/aux/DynamicDataTypes.cpp Lodestar/blocks/std/ConverterBlock.cpp Lodestar/blocks/std/ConverterBlock.hpp Lodestar/blocks/std/MuxBlock.cpp Lodestar/blocks/std/MuxBlock.hpp Lodestar/blocks/std/DemuxBlock.cpp Lodestar/blocks/std/DemuxBlock.hpp Lodestar/blocks/std/ReImToComplexBlock.cpp Lodestar/blocks/std/ReImToComplexBlock.hpp Lodestar/blocks/std/SaturationBlock.cpp Lodestar/blocks/std/SaturationBlock.hpp Lodestar/blocks/std/SwitchBlock.cpp Lodestar/blocks/std/SwitchBlock.hpp Lodestar/blocks/std/geometry/QuaternionBlock.cpp Lodestar/blocks/std/geometry/QuaternionBlock.hpp Lodestar/blocks/BlockType.hpp Lodestar/blocks/BlockTraits.cpp Lodestar/blocks/BlockTraits.hpp Lodestar/blocks/aux/DirectedGraph.cpp Lodestar/blocks/aux/DirectedGraph.hpp Lodestar/blocks/aux/StronglyConnectedComponents.cpp Lodestar/blocks/aux/StronglyConnectedComponents.hpp Lodestar/blocks/BlockPack.cpp Lodestar/blocks/BlockPack.hpp Lodestar/blocks/aux/Executor.cpp Lodestar/blocks/aux/Executor.hpp Lodestar/aux/DemangledType.cpp Lodestar/aux/DemangledType.hpp Lodestar/blocks/std/systems/DiscreteStateSpaceBlock.cpp Lodestar/blocks/std/systems/DiscreteStateSpaceBlock.hpp Lodestar/aux/FunctionTraits.hpp)

#    if (CMAKE_BUILD_TYPE MATCHES Debug)
#        target_link_libraries(liblodestar Catch2::Catch2)
#    endif ()
#
#    if (WITH_PROTOBUF)
#        target_link_libraries(liblodestar ${Protobuf_LIBRARIES})
#    endif ()
#
#    if (WITH_GINAC)
#        target_link_libraries(liblodestar ${GINAC_LIBRARY})
#        target_link_libraries(liblodestar ${CLN_LIBRARY})
#    endif ()
#
#    if (WITH_NNG)
#        target_link_libraries(liblodestar nng pthread)
#    endif ()

    target_include_directories(liblodestar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Lodestar)

    set_target_properties(liblodestar PROPERTIES
            VERSION 0.0.1
            OUTPUT_NAME Lodestar)
endif ()