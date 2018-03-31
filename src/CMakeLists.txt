include(CodeCoverage)

SET(GCC_COMPILE_FLAGS "-Wall -pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")

include_directories(inc)

set(SRC figures.cpp)
set(TEST_SRC ${SRC} catch.cpp test.cpp misc.cpp)

add_executable(figures main.cpp ${SRC})
add_executable(figures_test ${TEST_SRC})

target_compile_options(figures_test PRIVATE -g3 -O0 -coverage)
set_target_properties(figures_test PROPERTIES LINK_FLAGS "${LINK_FLAGS} -coverage")
