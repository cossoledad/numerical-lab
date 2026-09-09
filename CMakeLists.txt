cmake_minimum_required(VERSION 3.16)

project(numerical_lab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(numerical_lab
    src/main.c
    src/root.c
    src/integration.c
    src/derivative.c
    src/ode.c
    src/matrix.c
    src/regression.c
    src/optimize.c
    src/monte_carlo.c
    src/statistics.c
    src/numeric_error.c
    src/utils.c
    src/big_number.c
    src/blist.c
)

target_include_directories(numerical_lab PRIVATE include)

if (MSVC)
    target_compile_options(numerical_lab PRIVATE /W4)
else()
    target_compile_options(numerical_lab PRIVATE -Wall -Wextra -Wpedantic)
    target_link_libraries(numerical_lab PRIVATE m)
endif()
