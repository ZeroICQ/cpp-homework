include_directories(inc)

set(SRC figures.cpp)
set(TEST_SRC ${SRC} catch.cpp test.cpp misc.cpp)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
SET(GCC_COVERAGE_LINK_FLAGS    "-lgcov")

SET( CMAKE_CXX_FLAGS_DEBUG        "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${GCC_COVERAGE_LINK_FLAGS}" )

add_executable(figures main.cpp ${SRC})
add_executable(figures_test ${TEST_SRC})