
from conans import ConanFile, CMake
class PdkConan(ConanFile):
    name = "pdk_Xtech"
    version = "0.2"
    license = ""
    author = "Bowen Song"
    description = "GenII-SiOI_500nmDemo"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = ("*", "!build*", "!cmake-build-*", "!.*", "!*.gch")
    requires = "Libmask/7.0@cmalips/stable"

    def package_id(self):
        self.info.settings.build_type = "Any"

    def package(self):
        self.copy("*.h", dst="include", src=".", excludes=("*cmake-build-*", "*build*"))
        self.copy("*.gch", dst="include", src=".", excludes="*cmake-build-*")
        self.copy("*.a", dst="lib", src="lib", keep_path=False)
        self.copy("*.gds", dst=".", src=".", keep_path=False, excludes="*mask_example.gds")
        self.copy("*.plf", dst=".", src=".", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["pdk_Xtech"] 