MazeSolver
==========

An application designed to generate random **solvable** mazes of *any* size, and solve them! The program uses an implementation of the A* algorithm to solve these mazes, clone the repo and give it a try yourself!

Unsolved | Solved
:-------:|:------:
![img](http://i.imgur.com/AxVHDz5.png) | ![img](http://i.imgur.com/9ydpJcD.png)

Your only limitation to the size of the maze is the sky itself (well, and the size of your console and monitor I guess). 

Building
----------------------------------------------------
There's no dependencies for this repo, *yay!*. All you need to worry about it building the project

Windows
---------
1. Clone the master MazeSolver repository in a directory of your choice.

2. Create a build folder. This project requires and out-of-tree build. This means you ~will be unable to~ **should not** run CMake in the MazeGen folder

3. Open up the CMake GUI. in the input box labelled "Where is the source code:", enter the full path to the source folder. In the input box labelled "Where to build the binaries" , enter the full path to the folder you created in step 2.

4. Press the "Configure" button. A window will pop up asking you which compiler to use. Selecter any version your heart desires but this tutorial will center around VS, so we're going to select to build a VS project. 

5. hit "Generate".

6. Open up the build folder, double click the Solution file and build the project. All done!

Linux
---------
1. `cmake /path/to/repository/source/tree`
