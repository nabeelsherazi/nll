cmake_minimum_required(VERSION 3.14)
project(nll_tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  nll_tests
  collections/test_linked_list.cpp
  collections/test_ring_buffer.cpp
  collections/test_hashmap.cpp
  collections/test_set.cpp
  graph/test_binary_tree.cpp
  graph/test_unweighted_graph.cpp
  geometry/test_point.cpp
  geometry/test_triangle.cpp
)
target_link_libraries(
  nll_tests
  nll_lib
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(nll_tests)