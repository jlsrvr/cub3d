# cub3d

This project is inspired by the world-famous Wolfenstein 3D game, the first FPS game. I explored teh technic of ray-casting. The goal was to make a dynamic view inside a maze, in which you'd have to find your way.

The executable had to be able to receive a scene description in the format of a path to a `.cub` file which defined the size of the display, the paths to different textures, as well as the layout of the map.

There were two parts to this project firstly parsing the scene description and then using this information to raycast the scene and have the player be able to move within the maze.

To achiev the display we were given the minilibx-linux.

Unit and integration tests for the parser can be found [here](https://github.com/jlsrvr/cub3d-specs)
