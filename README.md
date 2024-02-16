# Gimbal lock and quaternions

A visualisation and comparison of normal and bump mapping models in OpenGL and how they alter the original appearance.

## About this repo

Gimbal lock is a phenomenon that occurs in three-dimensional rotational systems, such as those used in computer graphics, animation, and aerospace applications. It arises when using Euler angles to represent the orientation of an object in three-dimensional space. Euler angles describe rotations about three distinct axes (pitch, yaw, and roll). However, when the pitch angle approaches +90 or -90 degrees, the rotation axes align, leading to a loss of one degree of freedom and making it impossible to represent specific orientations uniquely. This results in a situation where rotations around one axis affect the other two, causing unexpected and undesirable behaviour in animations or control systems.

This repository contains an OpenGL environment designed for visualising Gimbal lock and demonstrating the corrective capabilities of quaternions. With this implementation, users can dynamically adjust real-time rotation angles, offering an interactive platform to visualise these cases.

## Demo video

[![Watch the video](https://img.youtube.com/vi/DxfHnhUArhE/0.jpg)](https://www.youtube.com/watch?v=DxfHnhUArhE)

## Getting Started

### Dependencies

- [Xcode 14.3.1](https://developer.apple.com/xcode/)
- OpenGL 4.1 (included in macOS)
- [Glew 2.2.0](https://glew.sourceforge.net)
- [GLFW 3.3.8](https://github.com/glfw/glfw)
- [Assimp 5.3.1](https://github.com/assimp/assimp)
- [GLM 1.0.0](https://github.com/g-truc/glm)

### Installing

1. Clone this repository.

```sh
git clone https://github.com/borjagq/Gimbal-lock/
```

2. Open the project ```Lab1.xcodeproj```

3. Build and run

# License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/borjagq/Gimbal-lock/LICENSE/) file for details

# Acknowledgments

This repository incorporates essential components from the open-source libraries [stb](https://github.com/nothings/stb) and [Dear ImGui](https://github.com/ocornut/imgui). These libraries provide the file read/write and GUI functionalities.  For further details about these libraries, visit their GitHub repositories.
