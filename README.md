# FENGINE
---
FEngine is an easy to use rendering library made to quickly get you started rendering 3D objects on the screen. It is designed for simplicity and ease-of-use not really performance.

## Adding to your project
If you are using cmake, adding FEngine to your library is really easy, simple clone the project with the `--recursive` flag, and call
`add_subdirectory()` on it in your main `CMakeLists.txt` file.

## Example
```cpp
#include <FEngine/FEngine.hpp>

int main(){

    // Initialize the fengine object
    FEngine engine("Window", 800, 600);

    // The loadObject function takes a path to a directory relative to the executable binary
    // The directory must at least contain a model.obj file
    // Optional files are albedo.png and ambient.png
    // albedo.png is the texture of the model
    // ambient.png is the ambient occlusion map of the model
    // It is okay to "load" the same object multiple times as the returned FObject will be cached so resources aren't duplicated
    FObject obj = engine.loadObject("res/cube", Color(255, 0, 255));

    // Push the camera behind so you can see the object
    engine.camera.position.z = -10;

    // This is the rendering loop
    while(engine.window.isOpen()){
        engine.draw(obj);
        engine.update(); // Make sure to call update at the end of the draw loop
    }

    // Cleanup resources after program is finished
    engine.destroy();

    return 0;
}
```
