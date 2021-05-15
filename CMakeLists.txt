cmake_minimum_required(VERSION 3.17)
project(Lodestar)

set(CMAKE_CXX_STANDARD 11)

option(WITH_GINAC "Use GiNaC" ON)
option(WITH_PROTOBUF "Use Protocol Buffers" ON)
option(MAKE_STATIC_LIB "Make static library" OFF)

include_directories("src")
include_directories("dep")
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")
#find_package(ginac REQUIRED 1.7.0)

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

    SET(PROTOBUF_INCLUDES src/io/proto/ls.proto.eigen.pb.cc src/io/proto/ls.proto.eigen.pb.h src/io/proto/ls.proto.systems.pb.cc src/io/proto/ls.proto.systems.pb.h src/io/proto/ls.proto.ginac.pb.cc src/io/proto/ls.proto.ginac.pb.h src/io/proto/ls.proto.symbolic.pb.cc src/io/proto/ls.proto.symbolic.pb.h src/block/StateSpaceBlock.cpp src/block/StateSpaceBlock.hpp)
else()
    UNSET(PROTOBUF_INCLUDES)
endif()

add_executable(Lodestar main.cpp src/primitives/Integrator.hpp src/primitives/integrators/IntegratorNewton.hpp src/analysis/BilinearTransformation.cpp src/analysis/BilinearTransformation.hpp src/systems/SystemStateless.hpp src/systems/StateSpace.cpp src/systems/StateSpace.hpp src/analysis/ZeroOrderHold.cpp src/analysis/ZeroOrderHold.hpp src/analysis/LinearSystemInverse.cpp src/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.hpp src/systems/TransferFunction.cpp src/systems/TransferFunction.hpp src/LodestarErrors.hpp src/LodestarErrorNames.hpp src/io/EigenProtoIface.cpp src/io/EigenProtoIface.hpp src/io/ProtoIfaceABC.hpp src/aux/UnitLiterals.hpp src/systems/DiscreteStateSpace.cpp src/systems/DiscreteStateSpace.hpp src/systems/DiscreteSystem.cpp src/systems/DiscreteSystem.hpp src/io/ProtoWrapper.cpp src/io/ProtoWrapper.hpp src/control/FixedGain.cpp src/control/FixedGain.hpp src/io/ProtoTypeTrait.hpp src/systems/SystemStateful.hpp src/symbolic/GiNaCNumTrait.hpp src/symbolic/OrdinaryDifferentialEquation.cpp src/symbolic/OrdinaryDifferentialEquation.hpp src/control/DiscreteLQR.cpp src/control/DiscreteLQR.hpp src/synthesis/AlgebraicRiccatiEquation.cpp src/synthesis/AlgebraicRiccatiEquation.hpp src/filter/DiscreteLQE.cpp src/filter/DiscreteLQE.hpp src/io/GiNaCProtoIface.cpp src/io/GiNaCProtoIface.hpp ${PROTOBUF_INCLUDES} src/block/Block.hpp src/block/StateSpaceBlock.cpp src/block/StateSpaceBlock.hpp)

if (WITH_PROTOBUF)
    target_link_libraries(Lodestar ${Protobuf_LIBRARIES})
endif()

if (WITH_GINAC)
    target_link_libraries(Lodestar ${GINAC_LIBRARY})
endif()

#if (MAKE_STATIC_LIB)
#    add_library(LoadstarLib STATIC src/primitives/Integrator.hpp src/primitives/integrators/IntegratorNewton.hpp src/analysis/BilinearTransformation.cpp src/analysis/BilinearTransformation.hpp src/systems/SystemStateless.hpp src/systems/StateSpace.cpp src/systems/StateSpace.hpp src/analysis/ZeroOrderHold.cpp src/analysis/ZeroOrderHold.hpp src/analysis/LinearSystemInverse.cpp src/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.hpp src/systems/TransferFunction.cpp src/systems/TransferFunction.hpp src/LodestarErrors.hpp src/LodestarErrorNames.hpp src/io/EigenProtoIface.cpp src/io/EigenProtoIface.hpp src/io/ProtoIfaceABC.hpp src/aux/UnitLiterals.hpp src/systems/DiscreteStateSpace.cpp src/systems/DiscreteStateSpace.hpp src/systems/DiscreteSystem.cpp src/systems/DiscreteSystem.hpp src/io/ProtoWrapper.cpp src/io/ProtoWrapper.hpp src/control/FixedGain.cpp src/control/FixedGain.hpp src/io/ProtoTypeTrait.hpp src/systems/SystemStateful.hpp src/symbolic/GiNaCNumTrait.hpp src/symbolic/OrdinaryDifferentialEquation.cpp src/symbolic/OrdinaryDifferentialEquation.hpp src/control/DiscreteLQR.cpp src/control/DiscreteLQR.hpp src/synthesis/AlgebraicRiccatiEquation.cpp src/synthesis/AlgebraicRiccatiEquation.hpp src/filter/DiscreteLQE.cpp src/filter/DiscreteLQE.hpp src/io/GiNaCProtoIface.cpp src/io/GiNaCProtoIface.hpp ${PROTOBUF_INCLUDES} src/block/Block.hpp)
#
#    if (WITH_PROTOBUF)
#        target_link_libraries(LoadstarLib ${Protobuf_LIBRARIES})
#    endif()
#
#    if (WITH_GINAC)
#        target_link_libraries(LoadstarLib ${GINAC_LIBRARY})
#    endif()
#endif()