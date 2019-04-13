Assignment
-------------

There is a Scene.json file in models/, which contains some basic paramaters that can be changed. You can also press SPACE toggle forcing the boids towards the center.

numBoids - the number of boids in the simulation.

avoidenceDistance - the radius at which boids will avoid each other.

cohesionDistance - the radius at which boids will attempt to match each other's velocity.

gatheringDistance -  the radius at which boids will attempt to gather together.

numIterations - the number of iterations that the simulation will make per timestep.






Documentation
-------------

https://lakin.ca/givr/

Compilation
-----------

## How to Install Dependencies (Ubuntu)

    sudo apt install cmake build-essential

## How to Build

    cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release
    cmake --build build

## How to Run

    build/simple
