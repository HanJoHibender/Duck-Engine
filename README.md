# Duck Engine

Duck Engine is an open-source voxel engine developed in C++ using OpenGL. It provides a foundation for creating voxel-based applications, games, simulations, and more. Please note that Duck Engine is in the early stages of development, and contributions and feedback are welcome.

## Early Development

Duck Engine is currently in its early development phase. While it offers some fundamental features and a foundation for voxel rendering, it may lack certain advanced capabilities and optimizations. You are encouraged to explore, experiment, and contribute to its growth.

## Features

- **Voxel Rendering:** Render voxel-based worlds, terrains, and structures.
- **OpenGL:** Utilize the power of modern OpenGL for efficient graphics rendering.
- **Cross-Platform:** Duck Engine is designed to run on various platforms, making it versatile for different applications.
- **Extensible:** Easily expand the engine's capabilities by adding custom shaders, components, and systems.
- **Efficient:** Optimized for performance to handle complex voxel scenes smoothly.
- **Open-Source:** Free and open for anyone to use, modify, and contribute to.

### Prerequisites

- C++ compiler (C++17 or higher)
- CMake (for building)
- OpenGL drivers compatible with your system
### Libraries
- [Glad](https://glad.dav1d.de/) (OpenGL loader)
- [GLFW](https://www.glfw.org/) (Window and input management)
- [glm](https://github.com/g-truc/glm) (Mathematics library)
- [stb](https://github.com/nothings/stb) (Image loading)

### Building

1. Clone the Duck Engine repository:

    ```git clone https://github.com/HanJoHibender/Duck-Engine.git```

2. Navigate to the directory

    ```cd DuckEngine```
3. Configure and generate build files using CMake:

    ```cmake .```

4. Build the project:

    ```make```

### Example Usage

Here is a simple example of how to create a Duck Engine application:

```cpp
#include <iostream>
#include "Engine.h"

using namespace DuckEngine;

int main() {
 Engine::Setup();

 Window window = Window(640, 480, "Bread");
 window.SetVsync(true);

 std::shared_ptr<Scene> scene = Scene::CreateScene(window);

 auto& camera = scene->CreateCamera();
 Transform* cameraTransform = ((Transform*)camera.GetComponent<Transform>());
 cameraTransform->Position += cameraTransform->FORWARD() * 0.1f;

 SceneObject vobj = scene->CreateObject();
 vobj.AddComponent<Renderable3D>();

 (FpsComponent*)vobj.AddComponent<FpsComponent>();

 Engine::Start();

 return 0;
}
```

Please be aware that Duck Engine is actively under development and may undergo changes and improvements. Feedback and contributions are appreciated.


Duck Engine is an open-source project, and contributions are welcome. If you'd like to contribute, please read our Contributing Guide.
License

This project is licensed under the GNU GPLv3 License - see the LICENSE file for details.
Acknowledgments

```
Thank you to the creators and maintainers of Glad, GLFW, glm, 
and stb for their amazing libraries that make Duck Engine possible.
```