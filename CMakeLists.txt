cmake_minimum_required(VERSION 3.14)

project(nabeels_little_library)

add_library(nll_lib INTERFACE)

find_package(fmt REQUIRED)

target_include_directories(nll_lib INTERFACE include)

target_compile_features(nll_lib INTERFACE cxx_std_17)

target_link_libraries(nll_lib INTERFACE fmt::fmt)

target_compile_options(nll_lib INTERFACE -fsanitize=address)
target_link_options(nll_lib INTERFACE -fsanitize=address)

add_subdirectory(tests)