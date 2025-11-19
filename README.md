# CUB3D

## Overview
This project uses 42s own graphics library to create a Raycasting Game in pure C in the tradition of Wolfenstein.

## Features
- Custom Map making including choosing wall textures
- Movement (W,A,S,D)

## Approach
The program checks the **maps validity**, uses the Digital Differential Analyzer **(DDA)** Algorithm to render the view and draws it using the functions provided by the schools MLX library.

## Map Creation
- The 4 first lines define the textures of the walls for each **cardinal direction** followed by a ```\n```
	- 1: North
	- 2: South
	- 3: West
	- 4: East
- The next two lines define **floor** and **ceiling** color in **r,g,b** followed by a ```\n```
- Everything else is considered part of the map. **1** indicates a wall, **0** an open space and the players position is identified by a capital letter according to the direction he faces followed by a ```\n```
	- N: North
	- S: South
	- W: West
	- E: East
- the map is considered valid only if it is fully enclosed in walls, the player is inside the enclosed space and there are no open spaces which are not fully enclosed either inside or outside the map.
	- valid: 
NO ./texture/CONCRETE_2A.xpm
SO ./texture/VENT_1A.xpm
WE ./texture/TECH_1A.xpm
EA ./texture/TECH_3G.xpm

F 20,22,25
C 13,14,15

        1111111111111111111111111
        1000000000000000000000001
        1000000000000001111111111
        1000000000E00001
111111111000000000000001
10000000000000000000000111111
11111111111111110000000000001
10000000000000000000000000001
10000111111111110000000000001
10000000000000000000000000001
10000000000000011111100000001
1001111111000001    100000011
10000011 1000001    100000001
11111111 1111111    111111111

	- invalid: 
NO ./texture/CONCRETE_2A.xpm
SO ./texture/VENT_1A.xpm
WE ./texture/TECH_1A.xpm
EA ./texture/TECH_3G.xpm

F 20,22,25
C 13,14,15

        1111111111111111111111111
   0    1000000000000000000000001
        1000000000000001111111111
        1000000000E00001
100111111000000000000001
10000000000000000000000111111
11111111111111110000000000001
10000000000000000000000000001
10000111111111110000000000001
10000000000000000000000000001
10000000000000011111100000001
1001111111000001    100000011
10000011 1000001    100000001
11111111 1111111    111111111

## Execution
Compilation: ```make```
Run: ```./cub3d "map_name"```