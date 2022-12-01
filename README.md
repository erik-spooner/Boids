Assignment #4
-------------

This assignment implements the concepts proposed by Craig W. Reynolds (Flocks, Herds, and Schools: A Distributed Behavioral Model). The main idea is that a mass spring model can be used to model the "flocking" behaviour of animals (In the paper Reynolds calls such animals with flocking behaviour as bird-oids or for short, boids). The boids are modeled as a particle with mass and a direction. When two boids are within a certain distance (the gathering distance) from eachother a spring force attempts to pull them together. When the boids are within a smaller distance (the cohesion distance) another force will be applied to try to match each other's velocity. Lastly if the boids are too close together (withing the avoidence distance), a spring force will be applied to each to push them apart. All together this allows boids to flock and potentially break off from the flock.

There is a Scene.json file in models/, which contains some basic paramaters that can be changed. You can also press SPACE to toggle pulling the boids towards the center.

numBoids - the number of boids in the simulation.

avoidenceDistance - the radius at which boids will avoid each other.

cohesionDistance - the radius at which boids will attempt to match each other's velocity.

gatheringDistance -  the radius at which boids will attempt to gather together.

numIterations - the number of iterations that the simulation will make per timestep.
