-- Build Instructions --

Dependencies:
	- GLFW
	- GLEW
	- GLM
	- ninja
	- pkg-config

Mac OS X:
	Add -framework OpenGL to the cflags in the build.ninja and run ninja in the main directory of the project.
	OR:
	Open a terminal and run the following commands:
	xcode-select --install
	Then go through the GUI installer, then type:
	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
	Then type the following:
	brew install clang
	brew install glfw
	brew install glm
	brew install glew
	brew install pkg-config
	brew install ninja
	 

Windows:
	Make sure the header files are included in your project folder like this:

		GLFW/glfw3.h
		GL/glew.h
		glm/glm.hpp, glm/gtc/noise.hpp etc..

	There are no binary build files for glm but obviously make sure to link against the glfw and glew bins.

Linux:
	Type in the following commands
	sudo apt-get install clang
	sudo apt-get install libglfw3-dev
	sudo apt-get install libglew-dev
	sudo apt-get install libglm-dev
	sudo apt-get install ninja
	sudo apt-get install pkg-config

	Then clone the repository and just run ninja in the main folder of the project. No modifications needed.
