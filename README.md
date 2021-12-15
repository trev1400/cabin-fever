README

IMPORTANT: texture map source images are ABSOLUTE file paths and must be changed for shader files to compile correctly. Find the FILE_PATH_PREFIX variable at the top of glwidget.cpp and change it to your machine's path.

Summary
	⁃	This project utilises OpenGL shapes to create a 3D scene of the interior of a cabin that sits atop a snowy mountain range. Through the window, we can see the terrain, falling snow, and thrown snowballs, as well pan around the inside of the cabin, which includes furniture, paintings, rugs, and a door.

Main Features
	⁃	Texture Mapping: Texture mapping is implemented on most shapes in our scene, including the cabin walls, roof, window, and furniture. 
	⁃	Terrain: The snowy terrain environment is generated with a triangle strip mesh with randomly generated y-coordinate values to mimic a natural irregular surface and bicubic interpolation to smooth out jagged edges
	⁃	Particle Generation: We used particle generation for implementing falling snow outside the window, which descends from the top of the screen at a constant rate
	⁃	Collision Detection: A thrown snowball detects collisions with a point on the window. When a collision is detected, the snowball explodes into small particles

Design Choices
	⁃	UI
	⁃	Snow Rate: controls the speed at which snow falls from the sky
	⁃	Snow Size: controls the size of each snowflake particle
	⁃	Snow Level: controls the height/amount of fallen snow
	⁃	Windiness: controls the number of peaks/frequency of the fallen snow
	⁃	Throw Snowball: throws a snowball at the window, which explodes upon contact
	⁃	GLWidget.cpp (main class)
	⁃	includes member variables for each object and program in scene
	⁃	all objects are initialised in initialiseGL(), including shader programs, textures, room (cabin), terrain, scene (environment eg. stars, moon), and particles (snow), each with a respective helper method
	⁃	loadTexture() loads all relevant textures once upon texture initialisation (as opposed to every time step when drawing)
	⁃	paintGL() calls helper methods that draw each component, which are made up of many openGL shapes
	⁃	mouse movements are tracked to update matrices accordingly to support panning

Improvements To Be Made
	⁃	Minor bugs in terrain from lab02 source code (miscellaneous triangles sometimes appear)
	⁃	Particle generation is currently 2D, which does not support panning (ie. trajectory of snowflakes stay the same on the screen regardless of where the camera looks)