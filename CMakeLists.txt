cmake_minimum_required(VERSION 3.8)
project(cpp_utils)

enable_testing()

add_library(cpp_utils INTERFACE)
target_sources(cpp_utils INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/ios.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/cpp_utils/scope_guard.hpp)
target_include_directories(cpp_utils INTERFACE include/)
target_compile_features(cpp_utils INTERFACE cxx_std_14)

add_subdirectory(test)
