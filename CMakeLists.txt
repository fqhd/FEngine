cmake_minimum_required(VERSION 3.23.2)
project(FEngine VERSION 1.0.0)

add_library(fengine STATIC src/Camera.cpp src/CascadeShadowMap.cpp src/Cube.cpp src/DeferredRenderer.cpp src/Fengine.cpp src/GBuffer.cpp src/GLTexture.cpp src/Image.cpp src/InputManager.cpp src/MasterRenderer.cpp src/Model.cpp src/OBJLoader.cpp src/Quad.cpp src/Shader.cpp src/Skybox.cpp src/SSAO.cpp src/SSAOBlur.cpp src/SSAOTexture.cpp src/Texture.cpp src/Transform.cpp src/Window.cpp include/Camera.hpp include/CascadeShadowMap.hpp include/Cube.hpp include/DeferredRenderer.hpp include/Fengine.hpp include/GBuffer.hpp include/GLTexture.hpp include/Image.hpp include/InputManager.hpp include/MasterRenderer.hpp include/Model.hpp include/OBJLoader.hpp include/Quad.hpp include/Shader.hpp include/Skybox.hpp include/SSAO.hpp include/SSAOBlur.hpp include/SSAOTexture.hpp include/Texture.hpp include/Transform.hpp include/Window.hpp include/stb_image.h include/FObject.hpp src/glad.c include/glad.h include/khrplatform.h)

set_property(TARGET fengine PROPERTY CXX_STANDARD 17)

target_include_directories(fengine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(fengine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/deps/include")
target_link_libraries(fengine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/deps/libs/glfw3.a")