cmake_minimum_required(VERSION 3.12)
project(ChangeMyName CXX)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_library(minesweeper_core src/MinesweeperBoard.cpp)
target_include_directories(minesweeper_core PUBLIC include)

add_library(minesweeper_text_view src/MSBoardTextView.cpp)
target_include_directories(minesweeper_text_view PUBLIC include)

add_library(minesweeper_text_controller src/MSTextController.cpp)
target_include_directories(minesweeper_text_controller PUBLIC include)

add_executable(sample_test tests/MinesweeperTests.cpp)
target_include_directories(sample_test PUBLIC include)
target_link_libraries(sample_test gmock_main gtest gmock minesweeper_core)

add_executable(minesweeper src/main.cpp)
target_link_libraries(minesweeper minesweeper_core  minesweeper_text_view minesweeper_text_controller)

add_custom_target(run_tests
                  COMMAND sample_test
                  DEPENDS sample_test)

enable_testing()
add_test(tests sample_test)
