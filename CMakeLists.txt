cmake_minimum_required(VERSION 3.23.2)
project(FEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(fengine SHARED src/Camera.cpp src/CascadeShadowMap.cpp src/Cube.cpp src/Fengine.cpp src/GBuffer.cpp src/GLTexture.cpp src/Image.cpp src/InputManager.cpp src/MasterRenderer.cpp src/Model.cpp src/OBJLoader.cpp src/Quad.cpp src/Shader.cpp src/Skybox.cpp src/Texture.cpp src/Transform.cpp src/Window.cpp src/glad.c src/FXAA.cpp)

find_library(ourGLFWLib glfw NAMES glfw glfw3 GLFW GLFW3 DOC "Windowing Library")
find_path(ourGLMLib glm NAMES glm GLM DOC "OpenGL Mathematics Library")
find_path(ourGLFWinclude glfw NAMES glfw GLFW3 GLFW GLFW3 DOC "Include directory for glfw")

target_include_directories(fengine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/FEngine)
target_include_directories(fengine PUBLIC ${ourGLFWinclude})
target_include_directories(fengine PUBLIC ${ourGLMLib})
target_link_libraries(fengine PRIVATE ${ourGLFWLib})

install(TARGETS fengine DESTINATION lib)
install(DIRECTORY include/FEngine DESTINATION include)

add_executable(out main.cpp)
target_link_libraries(out PRIVATE fengine)