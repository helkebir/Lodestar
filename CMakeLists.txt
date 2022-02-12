cmake_minimum_required(VERSION 3.11)
project(Lodestar VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(${CMAKE_SOURCE_DIR}/Lodestar/LodestarConfig.hpp.in ${CMAKE_SOURCE_DIR}/Lodestar/LodestarConfig.hpp)

# Force use of MPL2 compatible licenses only.
add_compile_definitions(EIGEN_MPL2_ONLY)

option(WITH_GINAC "Use GiNaC" ON)
option(WITH_PROTOBUF "Use Protocol Buffers" OFF)
option(WITH_NNG "Use NNG" ON)
option(MAKE_STATIC_LIB "Make static library" ON)

include_directories("${CMAKE_SOURCE_DIR}")
include_directories("dep")
include_directories("tests")
include_directories("dep/nanopb")
include_directories("dep/ersatz")
include_directories("dep/ersatz/ersatz/dep")

remove_definitions(LS_USE_GINAC)

file(GLOB_RECURSE LODESTAR_HEADERS "Lodestar/*.hpp" "Lodestar/*.pb.h")
file(GLOB_RECURSE LODESTAR_SOURCES "Lodestar/*.cpp" "Lodestar/*.pb.c")

file(GLOB_RECURSE ERSATZ_HEADERS "dep/ersatz/ersatz/*.hpp")
file(GLOB_RECURSE ERSATZ_SOURCES "dep/ersatz/ersatz/*.cpp")

file(GLOB_RECURSE NANOPB_BASE_HEADERS "dep/nanopb/*.h")
file(GLOB_RECURSE NANOPB_BASE_SOURCES "dep/nanopb/*.c")

add_library(Lodestar STATIC ${LODESTAR_SOURCES} ${LODESTAR_HEADERS} ${ERSATZ_SOURCES} ${ERSATZ_HEADERS} ${NANOPB_BASE_SOURCES} ${NANOPB_BASE_HEADERS})
set_target_properties(Lodestar PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Lodestar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Lodestar)

set_target_properties(Lodestar PROPERTIES
        VERSION ${PROJECT_VERSION}
        OUTPUT_NAME Lodestar)

#install(DIRECTORY Lodestar DESTINATION include)
foreach ( file ${LODESTAR_HEADERS} )
    get_filename_component( dir ${file} DIRECTORY )
    file(RELATIVE_PATH rel_dir ${CMAKE_CURRENT_SOURCE_DIR} ${dir})
    install( FILES ${file} DESTINATION include/${rel_dir} )
endforeach()
install(TARGETS Lodestar DESTINATION lib)
install(DIRECTORY dep/Eigen/ DESTINATION include/Lodestar/Eigen)
install(DIRECTORY dep/ersatz/ersatz DESTINATION include/Lodestar/ersatz)
install(DIRECTORY dep/nanopb/ DESTINATION include/Lodestar)
install(DIRECTORY dep/ersatz/ersatz/dep/fmt DESTINATION include/Lodestar/fmt)
install(DIRECTORY dep/unsupported/ DESTINATION include/Lodestar/unsupported)
install(FILES cmake/config/LodestarConfig.cmake DESTINATION lib/cmake/Lodestar)


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

    target_link_libraries(Lodestar ${GINAC_LIBRARY})
    target_link_libraries(Lodestar ${CLN_LIBRARY})
endif ()

if (WITH_PROTOBUF)
    MESSAGE("Building with Protocol Buffers.")
    add_compile_definitions(LS_USE_PROTOBUF)

    # Find Protobuf
    find_package(Protobuf REQUIRED)
    include_directories(${Protobuf_INCLUDE_DIRS})

    file(GLOB PROTOBUF_INCLUDES "Lodestar/io/proto/*.pb.c" "Lodestar/io/proto/*.pb.h" "Lodestar/io/proto/*.hpp")

    target_link_libraries(Lodestar ${Protobuf_LIBRARIES})
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

    target_link_libraries(Lodestar nng pthread)
endif ()

# Nanopb glob include
file(GLOB NANOPB_INCLUDES "dep/nanopb/pb*.c" "dep/nanopb/pb*.h" "Lodestar/io/proto/*.pb.c" "Lodestar/io/proto/*.pb.h" "Lodestar/io/proto/nano/*.pb.c" "Lodestar/io/proto/nano/*.pb.h")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    MESSAGE("Building in debug mode.")

    Include(FetchContent)

    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG v2.13.1)

    FetchContent_MakeAvailable(Catch2)

    file(GLOB_RECURSE LODESTAR_TESTS "tests/*_test.cpp")

    add_executable(Lodestar-test
            tests/TestMain.cpp
            ${NANOPB_INCLUDES}
            ${LODESTAR_TESTS}
    )

    target_link_libraries(Lodestar-test Lodestar)

    target_link_libraries(Lodestar-test Catch2::Catch2)

#    if (WITH_PROTOBUF)
#        target_link_libraries(Lodestar-test ${Protobuf_LIBRARIES})
#    endif ()
#
#    if (WITH_GINAC)
#        target_link_libraries(Lodestar-test ${GINAC_LIBRARY})
#        target_link_libraries(Lodestar-test ${CLN_LIBRARY})
#    endif ()
#
#    if (WITH_NNG)
#        target_link_libraries(Lodestar-test nng pthread)
#    endif ()
endif()