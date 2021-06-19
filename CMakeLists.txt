cmake_minimum_required(VERSION 3.17)
project(Lodestar)

set(CMAKE_CXX_STANDARD 11)

# Force use of MPL2 compatible licenses only.
add_compile_definitions(EIGEN_MPL2_ONLY)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
#include("${CMAKE_SOURCE_DIR}/cmake/modules/FindProtobuf.cmake")

option(WITH_GINAC "Use GiNaC" ON)
option(WITH_PROTOBUF "Use Protocol Buffers" OFF)
option(WITH_NNG "Use NNG" ON)
option(MAKE_STATIC_LIB "Make static library" OFF)

include_directories("src")
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

    if(GINAC_INCLUDE_DIR AND GINAC_LIBRARY)
        message("Found GiNaC.")
    else(GINAC_INCLUDE_DIR AND GINAC_LIBRARY)
        message(SEND_ERROR "Missing GiNaC library")
    endif(GINAC_INCLUDE_DIR AND GINAC_LIBRARY)

    message("Building with GiNaC.")
    include_directories(${GINAC_INCLUDE_DIR})
endif()

if (WITH_PROTOBUF)
    MESSAGE("Building with Protocol Buffers.")
    add_compile_definitions(LS_USE_PROTOBUF)

    # Find Protobuf
    find_package(Protobuf REQUIRED)
    include_directories(${Protobuf_INCLUDE_DIRS})

#    FindProtobuf("${PROJECT_SOURCE_DIR}/src/io/proto")

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

    file(GLOB PROTOBUF_INCLUDES "src/io/proto/*.pb.cc" "src/io/proto/*.hpp")
else()
    UNSET(PROTOBUF_INCLUDES)
endif()

if (WITH_NNG)
    find_library(NNG_LIBRARY nng)

    if (NOT NNG_LIBRARY)
        message(FATAL_ERROR "NNG was not found.")
    endif()

    add_compile_definitions(LS_USE_NNG)
    MESSAGE("Building with NNG.")
endif()

# Nanopb glob include

file(GLOB PROTOBUF_INCLUDES "src/io/proto/nano/*.pb.c" "src/io/proto/nano/*.pb.h")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    MESSAGE("Building in debug mode.")

    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v2.13.1)

    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(Lodestar src/primitives/Integrator.hpp src/primitives/integrators/IntegratorNewton.hpp src/analysis/BilinearTransformation.cpp src/analysis/BilinearTransformation.hpp src/systems/SystemStateless.hpp src/systems/StateSpace.cpp src/systems/StateSpace.hpp src/analysis/ZeroOrderHold.cpp src/analysis/ZeroOrderHold.hpp src/analysis/LinearSystemInverse.cpp src/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.cpp src/systems/TransferFunction.cpp src/systems/TransferFunction.hpp src/LodestarErrors.hpp src/LodestarErrorNames.hpp src/io/EigenProtoIface.cpp src/io/EigenProtoIface.hpp src/io/ProtoIfaceABC.hpp src/aux/UnitLiterals.hpp src/systems/DiscreteStateSpace.cpp src/systems/DiscreteStateSpace.hpp src/systems/DiscreteSystem.cpp src/systems/DiscreteSystem.hpp src/io/ProtoWrapper.cpp src/io/ProtoWrapper.hpp src/control/FixedGain.cpp src/control/FixedGain.hpp src/io/ProtoTypeTrait.hpp src/systems/SystemStateful.hpp src/symbolic/OrdinaryDifferentialEquation.cpp src/symbolic/OrdinaryDifferentialEquation.hpp src/control/DiscreteLQR.cpp src/control/DiscreteLQR.hpp src/synthesis/AlgebraicRiccatiEquation.cpp src/synthesis/AlgebraicRiccatiEquation.hpp src/filter/DiscreteLQE.cpp src/filter/DiscreteLQE.hpp src/io/GiNaCProtoIface.cpp src/io/GiNaCProtoIface.hpp ${PROTOBUF_INCLUDES} dep/nanopb/pb_common.c dep/nanopb/pb_common.h dep/nanopb/pb.h dep/nanopb/pb_decode.c dep/nanopb/pb_decode.h dep/nanopb/pb_encode.c dep/nanopb/pb_encode.h src/aux/CompileTimeQualifiers.hpp tests/TestMain.cpp tests/systems/StateSpace_test.cpp tests/primitives/integrators/IntegratorNewton_test.cpp tests/systems/TransferFunction_test.cpp tests/catchOnce.hpp src/block/BlockBase.hpp src/block/Block.hpp src/aux/Conjunction.hpp src/block/Ticket.hpp src/aux/RecursionException.hpp tests/block/Block_test.cpp tests/TestAuxFunctions.hpp src/block/std/Mux.hpp src/aux/Repeat.hpp src/aux/Indices.hpp src/block/std/Demux.hpp src/block/std/Multiply.hpp src/aux/AlgebraicOperators.hpp src/aux/OperationTypes.hpp src/aux/BinOpCheck.hpp src/aux/PairUp.hpp src/aux/TypeName.hpp src/aux/Pack.hpp src/time/Metronome.hpp src/time/TimeResolution.hpp tests/time/Metronome_test.cpp src/time/TimeDuration.hpp src/io/nng/Publisher.cpp src/io/nng/Publisher.hpp tests/io/proto/nano/Nanopb_test.cpp src/io/proto/nano/NanopbWrapper.hpp src/filter/SimpleMovingAverage.h src/aux/ArrayStack.hpp tests/aux/ArrayStack_test.cpp tests/filter/SimpleMovingAverage_test.cpp src/core/StatusOr.hpp src/core/Status.hpp tests/core/Status_test.cpp src/core/Status.cpp tests/demo/Car_test.cpp tests/demo/CarDemoFunctions.hpp src/data/FastFourierTransform.cpp src/data/FastFourierTransform.hpp tests/data/FastFourierTransform_test.cpp src/primitives/differentiators/BackwardDifference.hpp tests/primitives/differentiators/BackwardDifference_test.cpp src/primitives/integrators/BogackiShampine.hpp src/primitives/integrators/ButcherTableau.hpp tests/primitives/integrators/ButcherTableau_test.cpp)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(Lodestar Catch2::Catch2)
endif()

if (WITH_PROTOBUF)
    target_link_libraries(Lodestar ${Protobuf_LIBRARIES})
endif()

if (WITH_GINAC)
    target_link_libraries(Lodestar ${GINAC_LIBRARY})
endif()

if (WITH_NNG)
    target_link_libraries(Lodestar nng pthread)
endif()

#if (MAKE_STATIC_LIB)
#    add_library(LoadstarLib STATIC src/primitives/Integrator.hpp src/primitives/integrators/IntegratorNewton.hpp src/analysis/BilinearTransformation.cpp src/analysis/BilinearTransformation.hpp src/systems/SystemStateless.hpp src/systems/StateSpace.cpp src/systems/StateSpace.hpp src/analysis/ZeroOrderHold.cpp src/analysis/ZeroOrderHold.hpp src/analysis/LinearSystemInverse.cpp src/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.hpp src/systems/TransferFunction.cpp src/systems/TransferFunction.hpp src/LodestarErrors.hpp src/LodestarErrorNames.hpp src/io/EigenProtoIface.cpp src/io/EigenProtoIface.hpp src/io/ProtoIfaceABC.hpp src/core/UnitLiterals.hpp src/systems/DiscreteStateSpace.cpp src/systems/DiscreteStateSpace.hpp src/systems/DiscreteSystem.cpp src/systems/DiscreteSystem.hpp src/io/ProtoWrapper.cpp src/io/ProtoWrapper.hpp src/control/FixedGain.cpp src/control/FixedGain.hpp src/io/ProtoTypeTrait.hpp src/systems/SystemStateful.hpp src/symbolic/GiNaCNumTrait.hpp src/symbolic/OrdinaryDifferentialEquation.cpp src/symbolic/OrdinaryDifferentialEquation.hpp src/control/DiscreteLQR.cpp src/control/DiscreteLQR.hpp src/synthesis/AlgebraicRiccatiEquation.cpp src/synthesis/AlgebraicRiccatiEquation.hpp src/filter/DiscreteLQE.cpp src/filter/DiscreteLQE.hpp src/io/GiNaCProtoIface.cpp src/io/GiNaCProtoIface.hpp ${PROTOBUF_INCLUDES} src/block/Block.hpp)
#
#    if (WITH_PROTOBUF)
#        target_link_libraries(LoadstarLib ${Protobuf_LIBRARIES})
#    endif()
#
#    if (WITH_GINAC)
#        target_link_libraries(LoadstarLib ${GINAC_LIBRARY})
#    endif()
#endif()