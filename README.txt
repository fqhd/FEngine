-- Build Instructions --

Dependencies:
	- GLFW
	- GLEW
	- GLM
	- ninja
	- pkg-config

Mac OS X:
	Add -framework OpenGL to the cflags in the build.ninja and run ninja in the main directory of the project.

Windows:
	Make sure deps are included in a folder like this:
		GLFW/glfw3.h
		GL/glew.h
		glm/glm.hpp, glm/gtc/noise.hpp etc..

Linux:
	Make sure you have the dependencies installed, and just run ninja in the main folder of the project. No modifications needed.
