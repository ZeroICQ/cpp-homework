include_directories(inc)

set(SRC figures.cpp)

add_executable(figures main.cpp ${SRC})

add_executable(figures_test test.cpp ${SRC})