from conans import ConanFile, CMake, tools

class CppUtils(ConanFile):
    name = "cpputils"
    version = "1.0.2"
    url = "https://github.com/PVIII/cpp_utils.git"
    license = "MIT"
    author = "Patrick WANG-FRENINGER <github@freninger.at>"
    description = "Just some utilities to make C++ more elegant."
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    build_requires = "Catch2/2.7.0@catchorg/stable"
    exports_sources = "include/**", "CMakeLists.txt", "test/CMakeLists.txt", "test/*.cpp"
    no_copy_source = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", True):
            cmake.test()

    def package(self):
        self.copy("*.hpp")
        self.copy("CMakeLists.txt")

    def package_id(self):
        self.info.header_only()
