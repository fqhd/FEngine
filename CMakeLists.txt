cmake_minimum_required(VERSION 3.23.2)
project(FEngine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add FEngine library (source code)
add_library(FEngine SHARED src/Camera.cpp src/CascadeShadowMap.cpp src/Cube.cpp src/Fengine.cpp src/GLTexture.cpp src/Image.cpp src/InputManager.cpp src/MasterRenderer.cpp src/Model.cpp src/OBJLoader.cpp src/Shader.cpp src/Skybox.cpp src/Texture.cpp src/Transform.cpp src/Window.cpp src/Timer.cpp)

# Compile dependencies
add_subdirectory(deps/glfw)
add_subdirectory(deps/glm)
add_subdirectory(deps/stb-cmake)
add_subdirectory(deps/glad-cmake)

# Link dependencies
target_link_libraries(FEngine PUBLIC glfw)
target_link_libraries(FEngine PUBLIC glm)
target_link_libraries(FEngine PUBLIC stb-cmake)
target_link_libraries(FEngine PUBLIC glad-cmake)
target_include_directories(FEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
