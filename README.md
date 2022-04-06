# Cub3D
**A raycasting game engine based on Wolfenstein 3D's engine from the 90's**

## Usage
Compile by running `make all`, then open the engine by running `./cub3D <config_file>`. Optional argument `--save` can be applied to save a screenshot in BMP format instead of opening a game window.

## Features
- A fully working Linux version
- Camera controls by mouse movement
- Comments in the code

## Errors
- Resolution is downsized after creating the MLX image, sometimes resulting in out of memory errors
- Resolution is seen as invalid for > MAX_INT (solvable by checking the strlen of the "integer")
- Dragging the window is almost impossible due to the mouse being locked in the center of the window on window focus
- Closing the window is almost impossible due to the same reason as the one mentioned above
- Everything under a newline starting from the map is ignored, even faulty characters

## Grade
[![94/100](https://badge42.vercel.app/api/v2/cl1o16nym001109lewimxyxs8/project/2138146)](https://github.com/JaeSeoKim/badge42)
