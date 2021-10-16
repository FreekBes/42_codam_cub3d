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
- 2 leaks from MLX that are somehow solvable, probably caused by the mlx_do_sync function (which should be mlx_sync instead)
- Everything under a newline starting from the map is ignored, even faulty characters
- The MLX Dynamic Library (on macOS) is removed by running `make -f lib/mlx clean`

## Grade

[![94/100](https://badge42.herokuapp.com/api/project/fbes/cub3d)](https://github.com/JaeSeoKim/badge42)
