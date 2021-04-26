cmake_minimum_required(VERSION 3.17)
project(Lodestar)

set(CMAKE_CXX_STANDARD 11)

include_directories("src")
include_directories("dep")

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

add_executable(Lodestar main.cpp src/primitives/Integrator.hpp src/primitives/integrators/IntegratorNewton.hpp src/analysis/BilinearTransformation.cpp src/analysis/BilinearTransformation.hpp src/systems/SystemStateless.hpp src/systems/StateSpace.cpp src/systems/StateSpace.hpp src/analysis/ZeroOrderHold.cpp src/analysis/ZeroOrderHold.hpp src/analysis/LinearSystemInverse.cpp src/analysis/LinearSystemInverse.hpp tests/analysis/LinearSystemInverse_test.hpp src/systems/TransferFunction.cpp src/systems/TransferFunction.hpp src/LodestarErrors.hpp src/LodestarErrorNames.hpp src/io/EigenProtoIface.cpp src/io/EigenProtoIface.hpp src/io/proto/ls.proto.eigen.pb.cc src/io/proto/ls.proto.eigen.pb.h src/io/proto/ls.proto.systems.pb.cc src/io/proto/ls.proto.systems.pb.h src/io/ProtoIfaceABC.hpp src/aux/UnitLiterals.hpp src/systems/DiscreteStateSpace.cpp src/systems/DiscreteStateSpace.hpp src/systems/DiscreteSystem.cpp src/systems/DiscreteSystem.hpp src/io/ProtoWrapper.cpp src/io/ProtoWrapper.hpp src/control/FixedGain.cpp src/control/FixedGain.hpp src/io/ProtoTypeTrait.hpp src/systems/SystemStateful.hpp)
target_link_libraries(Lodestar ${Protobuf_LIBRARIES})