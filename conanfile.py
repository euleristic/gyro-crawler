from conan import ConanFile
from conan.tools.cmake import cmake_layout

class GameRecipe(ConanFile):
	settings = "os", "compiler", "build_type", "arch"
	generators = "CMakeToolchain", "CMakeDeps"
	
	package_type = "application"

	def requirements(self):
		self.requires("glfw/3.4")
		self.requires("glad/0.1.36")
		self.requires("glm/cci.20230113")
		self.requires("stb/cci.20230920")

	def configure(self):
		self.options["glad"].gl_profile = "core"
		self.options["glad"].gl_version = "4.3"

	def layout(self):
		cmake_layout(self)

