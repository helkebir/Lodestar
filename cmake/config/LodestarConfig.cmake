add_library(Lodestar STATIC IMPORTED)
find_library(LODESTAR_LIBRARY_PATH Lodestar HINTS "${CMAKE_CURRENT_LIST_DIR}/../../")
set_target_properties(Lodestar PROPERTIES IMPORTED_LOCATION "${LODESTAR_LIBRARY_PATH}")
target_include_directories(Lodestar INTERFACE ${CMAKE_INSTALL_PREFIX}/include/Lodestar)