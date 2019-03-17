cmake_minimum_required(VERSION 3.8)

add_executable(cpp_utils_test
               ios_test.cpp
               scope_guard_test.cpp)
target_link_libraries(cpp_utils_test PRIVATE cpp_utils CONAN_PKG::Catch2)

add_executable(cpp_utils_test_cpp17
               ios_test_cpp17.cpp
               scope_guard_test_cpp17.cpp)
target_link_libraries(cpp_utils_test_cpp17 PRIVATE cpp_utils CONAN_PKG::Catch2)
target_compile_features(cpp_utils_test_cpp17 PRIVATE cxx_std_17)

add_test(NAME test COMMAND cpp_utils_test)
add_test(NAME test_cpp17 COMMAND cpp_utils_test_cpp17)
