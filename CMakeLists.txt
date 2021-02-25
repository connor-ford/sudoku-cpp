cmake_minimum_required(VERSION 3.12)
project(sudoku VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB sudoku_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
add_executable(sudoku ${sudoku_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
