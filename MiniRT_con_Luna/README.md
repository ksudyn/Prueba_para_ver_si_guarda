*This project has been created as part of the 42 curriculum by ksudyn, ldel-val.*

# miniRT

## Description
**miniRT** is an introductory project into the world of Raytracing. It allows you to render computer-generated images using basic raytracing techniques, simulating how light rays interact with objects to create realistic 3D scenes from scratch.

**miniRT** is a project enables you to:
- **Render 3D Images:** Create visual outputs using ray-object intersection algorithms.
- **Understand Key Concepts:** Work with cameras, light sources (Ambient and Point lights), and geometric primitives (Spheres, Planes, and Cylinders).
- **Apply Mathematical Formulas:** Implement linear algebra and quadratic equations to solve intersections in 3D space.

## Instructions

### Prerequisites
- A Unix-based system (Linux or macOS).
- **X11** and **Xext** libraries.
- `gcc` or `cc` compiler and `make`.

### Instructions

### Compilation
To compile the project, run:
```bash
make
```

### Execution
Run the program with a scene description file:
```bash
./miniRT scenes/example.rt
```

### Controls
- **ESC / Window X:** Closes the program and frees all memory.
- **W, A, S, D:** Move the camera (Forward, Left, Backward, Right).
- **SPACE / SHIFT:** Move the camera Up or Down.
- **Arrow Keys:** Rotate the camera view (Pitch and Yaw).
- **+ / - Keys:** Adjust the Field of View (FOV).

### Scene Elements (RT Map)
The .rt file defines the scene layout using the following format:
- **Ambient Light (A):** `A [ratio] [R,G,B]` - Global lighting intensity and color.
- **Camera (C):** `C [x,y,z] [v_x,v_y,v_z] [FOV]` - Position, orientation vector, and field of view.
- **Light (L):** `L [x,y,z] [brightness] [R,G,B]` - Point light source position and intensity.
- **Sphere (sp):** `sp [center x,y,z] [diameter] [R,G,B]`
- **Plane (pl):** `pl [point x,y,z] [normal v_x,v_y,v_z] [R,G,B]`
- **Cylinder (cy):** `cy [center x,y,z] [axis v_x,v_y,v_z] [diameter] [height] [R,G,B]`

### Technical Implementation

#### Intersection Formulas
- **Sphere:** Based on the 3D formula $(x - h)^2 + (y - k)^2 + (z - l)^2 = r^2$. We solve for the ray equation $P = O + tD$.
- **Plane:** Represented as $ax + by + cz + d = 0$. The intersection is found where the ray hits the plane defined by its normal vector.
- **Cylinder:** Solved by intersecting a ray with an infinitely long cylinder and then clipping the result based on the specified height.

#### Shading and Color
- **Initial Color:** The object's base color multiplied by the ambient light.
- **Diffuse Lighting:** Calculated based on the angle between the normal vector at the intersection point and the light vector (Lambert's Cosine Law).
- **Shadows:** A shadow ray is cast from the intersection point to the light source. If an object is found in between, the point remains in shadow.
- **Final Color:** The sum of ambient and diffuse components, ensuring the values stay within the [0, 255] RGB range.

#### Data Structures
- **t_scene / t_data:** Main structures holding object lists (spheres, planes, cylinders), camera settings, and light information.
- **t_camera:** Stores FOV, origin, and orientation (using Euler angles or vectors) to calculate the ray direction for each pixel.

### Resources

#### Documentation
- **Scratchapixel:** Primary resource for Ray Tracing foundations.
- **Phong Reflection Model:** Logic for lighting and shading.
- **MinilibX Docs:** Window and event management.

#### Use of AI
AI (specifically Google Gemini) was used as a collaborative tool for:
- **Memory Management Debugging:** Fixing "still reachable" blocks and double-free errors in the parser and `get_next_line` logic.
- **Parser Optimization:** Refactoring the `read_file` loop to handle errors safely without leaving residues in memory.
- **Logic Refinement:** Assisting in the implementation of mathematical formulas for ray-object intersections and shading.
- **Technical Writing:** Structuring and translating this documentation to ensure clarity and professional standards.

### Compatibility
The project includes cross-platform support for **Linux** and **macOS**. The `Makefile` automatically detects the OS to link the correct libraries (X11/Xext for Linux or OpenGL/AppKit for macOS) and handles keycode differences for keyboard interaction.
```