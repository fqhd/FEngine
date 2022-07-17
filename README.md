# FENGINE
---
## Dependencies
- GLFW
- GLM
- CMake

### Mac OS
`brew install glfw glm`

### Ubuntu
`sudo apt install libglm-dev libglfw3-dev`

## Build Instructions
Note: Make sure you have dependencies installed first
1. Clone the repository `git clone https://github.com/fqhd/FEngine.git`
1. CD into the repository `cd FEngine`
1. Make the build folder and cd into it `mkdir build && cd build`
1. Create cmake config files `cmake ..`
1. Build the project `cmake --build .`
1. Move the res folder into the build directory `mv -r ../res build`
1. Run the executable binary `./out`
