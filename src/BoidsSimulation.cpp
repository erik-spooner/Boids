//
//

#include "BoidsSimulation.h"


BoidsSimulation::BoidsSimulation()
{
  // Create some Boids
  for (int i = 0; i < 10000; ++i) {
    float x = (random() % 10000) / 100.0f - 50.0f;
    float y = (random() % 10000) / 100.0f - 50.0f;
    float z = (random() % 10000) / 100.0f - 50.0f;
    
    float vx = (random() % 1000) / 10.0f - 50.f;
    float vy = (random() % 1000) / 10.0f - 50.f;
    float vz = (random() % 1000) / 10.0f - 50.f;

    boids.push_back(Boid(vec3(x,y,z), vec3(vx, vy, vz)));
  }
  
  
  //auto palmTree = Mesh(Filename("../models/Palm_Tree.obj"));
  
  // create the visual for the boid
  boidInstacedRenerable = createInstancedRenderable(Sphere(), Phong(Colour(0.0, 1.0, 1.0), LightPosition(2., 2., 15.)));
}

BoidsSimulation::~BoidsSimulation()
{
  
}

void BoidsSimulation::step(float timeStep)
{
  float dt = timeStep / (float) iterations;
  
  for (int iter = 0; iter < iterations; ++iter) {
    
    // Place the boids onto the grid
    for (int i = 0; i < (int)boids.size(); ++i) {
      grid.addBoidToGrid(i, boids[i].getPosition());
    }
    
    // Apply forces to the boids
    for (int i = 0; i < (int)boids.size(); ++i) {
      // Get all the nearby boids
      vector<int> indices;
      grid.getBoids(boids[i].getPosition(), gatheringDistance, indices);
      
      for (int j : indices) {
        if (i == j)
          continue;
        
        // calculate distance
        float distance = length(boids[i].getPosition() - boids[j].getPosition());
        
        // Apply avoidence forces
        if (distance < avoidenceDistance) {
          vec3 direction = normalize(boids[i].getPosition() - boids[j].getPosition());
          
          // attach a spring
          float k = 5.0;
          vec3 force = - k * (distance - avoidenceDistance) * direction;
          
          boids[i].applyForce(force);
        }
        // Cohesion forces
        else if (distance < cohesionDistance) {
          // apply a force to make the velocities match
          vec3 force = boids[j].getVelocity() - boids[i].getVelocity();
          force = 0.2f * force;
          
          boids[i].applyForce(force);
        }
        // Gathering forces
        else if (distance < gatheringDistance) {
          vec3 direction = normalize(boids[i].getPosition() - boids[j].getPosition());
          
          // attach a spring
          float k = 1.0;
          vec3 force = -k * ((gatheringDistance - distance) / 1000.0f) * direction;
          
          boids[i].applyForce(force);
        }
      }
      
      vec3 pos = boids[i].getPosition();
      if (length(pos) < maxDistanceFromOrigin)
        continue;
      
      vec3 force = 0.2f * -pos - 0.2f * boids[i].getVelocity();
      
      vec3 banking = vec3(0.0);
      if (length(pos) > 0.001)
        banking = cross(normalize(pos), boids[i].getNormal());
      
      force += banking * 30.f;
      
      boids[i].applyForce(force);
    }
    
    grid.tick();
    
    //move the boids
    for (int i = 0; i < (int)boids.size(); ++i) {
      boids[i].move(dt);
    }
  }
}

void BoidsSimulation::drawSimulation(const ViewContext<TurnTableCamera, PerspectiveProjection> &view)
{
  // Draw the boids
  for (int i = 0; i < (int)boids.size(); ++i) {
    mat4f transform = boids[i].getTransform();
    addInstance(boidInstacedRenerable, transform);
  }
  
  draw(boidInstacedRenerable, view);
}


