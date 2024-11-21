# Overview  

Pathfinder is an implementation of the A* pathfinding algorithm.  
It is written in C++ and it uses SFML to give a visualization to the algorithms solving process. 

The program utilizes CMake as it's build system. It works on macOS, Linux and on Windows (using the Visual Studio -program).  
 
NOTE:  
There are still few edge cases where the algorithm fails to find the shortest route from start to finish. I'm still in the process of developing this program, so these bugs will be fixed during the next few weeks.

# Installation

Instructions on how to use the program.

## Prerequisites

1. You need to install **CMake** and **Git** in order to be able to compile this project.  
2. On Windows, you need the Visual Studio -program.  
3. If you use Linux, install SFML's dependencies using your system package manager. On Ubuntu and other Debian-based distributions you can use the following commands:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```

## Compilation instructions

Run the following commands in your terminal:

1. ```git clone https://github.com/panu-kangas/pathfinder && cd pathfinder```  
2. ```cmake -B build```  
3. ```cmake --build build```
4. ```./pathfinder```

# About the program

In this pathfinder program, the user can place a "start tile" and "finish tile" on a tile grid map. Once these tiles have been set, the program utilizes the A* pathfinding algorithm to calculate and show the shortest route from start to finish.  
The user can also place walls on the tile grid map and thus create more challenge for the algorithm (because... you can't go through walls, right?).  
There are a few bugs in the pathfinding algorithm, but I am about to fix them!!
 
The shortest route is counted based on the assumption, that movement in the tile grid can only be done in up/down & left/right directions, and every move has an equal "movement cost" of 1. 

The tile information is displayed with the following color codes: 

| TILE TYPE | COLOR |
| ------------- | ------------- |
| Empty tile | White |
| Start tile | Dark green |
| Finish tile | Blue |
| Wall tile | Black |
| Processed tile | Yellow |
| Shortest route tile | Light green | 

A processed tile is one that the algorithm has checked in order to find the shortest route, but hasn't then used as a part of the final route.


The user can also see the algorithm's movement calculations by pressing the D -key. These calculations include "movement cost to start tile" in dark green number, the "movement cost to finish tile" in blue number, and then the most important number: the combined start & finish movement cost, which then determines what tile the algorithm chooses to analyze further.

 
### Controls

| KEY | ACTION |
| ------------- | ------------- |
| Left mouse button | Click on a tile to change it's status |
| W, E, S & F | After clicking, change the tile status by pressing W (for Wall), E (for Empty), S (for Start) or F (for Finish) |
| D | Press D to see the algorithm's calculation data for finding the shortest route. |


# Future develompent ideas

I want to optimize the algorithm a bit and also fix the few bugs that the program still has... 😁


