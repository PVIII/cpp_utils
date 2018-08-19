cmake_minimum_required(VERSION 3.8)

add_executable(cpp_utils_test ios_test.cpp)
target_link_libraries(cpp_utils_test PUBLIC cpp_utils)
target_include_directories(cpp_utils_test PUBLIC
                           ${CMAKE_CURRENT_BINARY_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(cpp_utils_test INTERFACE cxx_std_14)

add_executable(cpp_utils_test_cpp17 ios_test_cpp17.cpp)
target_link_libraries(cpp_utils_test_cpp17 PUBLIC cpp_utils)
target_include_directories(cpp_utils_test_cpp17 PUBLIC
                           ${CMAKE_CURRENT_BINARY_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(cpp_utils_test_cpp17 INTERFACE cxx_std_17)
set_target_properties(cpp_utils_test_cpp17 PROPERTIES CXX_STANDARD 17)

add_test(NAME test COMMAND cpp_utils_test)
add_test(NAME test_cpp17 COMMAND cpp_utils_test_cpp17)

