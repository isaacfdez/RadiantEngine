# Radiant Engine

Basic engine created for UPC's Master in Advanced Programming for AAA Videogames Assignment 1.

## Features

- 3D Scene view with Unity-like controls.
- Loading basic 3D models and textures into the scene by dragging and dropping files.
- Basic console log.
- Basic configuration and properties panels.

## How to use

### Loading models and textures

- Drag model files (.fbx) inside the engine window to load it and replace the current model.
- Drag texture files (.png, .dds, .jpg, .jpeg, .tga) to load them in the current model replacing the previous textures.

### Menu items

- File
  - Quit: Exit the engine.

- External Links
  - Go to Radiant Engine Github repository.

- Windows
  - Lets you toggle on an off the diferent windows of the engine.

### Move around the scene

Left click outside of the information windows to focus on the scene.

- While Right-clicking the mouse:
  - W to move forward.
  - S to move backwards.
  - A to move to the left.
  - D to move to the right.
  - Q to move downwards.
  - E to move upwards.
  - Move mouse to rotate the camera.
  - Shift to duplicate movement speed.
- Alt + Left-click to orbit around the camera focus
- Mouse wheel to zoom.
- F key to focus in front of the model.

### Configuration window

This window contains engine information and configuration variables for different modules:

- FPS Graph
  - Shows a FPS and MS graph.
- Hardware Information
  - Information about CPU, GPU and RAM.
- Libraries' Versions
  - Shows the versions of the libraries used in the engine.
- Window
  - Change window mode
    - Window
    - Borderless
    - Fullscreen 
    - Desktop Fullscreen
  - Resize window only if the mode is Window or Borderless.
- Camera
  - Frustum's Front information.
  - Frustum's Up information.
  - Camera position information.
  - Near Plane information.
  - Far Plane information.
  - FOV information.
  - Aspect Ratio information.
  - Movement speed information.
  - Rotation speed information.
  - Zoom speed information.

### Properties window

This window contains information about the currently loaded model

- Transformation
  - Position
  - Rotation
  - Scale
- Geometry 
  - For each mesh
    - Number of vertices.
    - Number of triangles.
    - Number of faces.
- Textures
  - For each texture
    - Preview of the image.
    - Dimensions of the texture.

### Console window

This window prints all logged information in the engine.

### About window

This window shows information related to the engine.

## Libraries used

- Assimp
- Dear ImGui
- DevIL
- GLEW
- MathGeoLib
- SDL

## Authors

Isaac Fernández Fontao (https://github.com/isaacfdez/)

## Github

https://github.com/isaacfdez/RadiantEngine

## License

[MIT](./LICENSE)
