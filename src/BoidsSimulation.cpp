//
//

#include "BoidsSimulation.h"

BoidsSimulation::BoidsSimulation(int nB, float aD, float cD, float gD, int iters) : numBoids(nB), iterations(iters), avoidenceDistance(aD), cohesionDistance(cD), gatheringDistance(gD), cellWidth(gD / 4.0f)
{
  // Create some Boids
  for (int i = 0; i < numBoids; ++i) {
    float x = (random() % 4000) / 100.0f - 20.0f;
    float y = (random() % 4000) / 100.0f - 20.0f;
    float z = (random() % 4000) / 100.0f - 20.0f;
    
    float vx = (random() % 1000) / 10.0f - 50.f;
    float vy = (random() % 1000) / 10.0f - 50.f;
    float vz = (random() % 1000) / 10.0f - 50.f;
    
    boids.push_back(Boid(vec3(x,y,z), vec3(vx, vy, vz)));
  }
  
  auto fish = Mesh(Filename("../models/fish.obj"));
  
  // create the visual for the boid
  boidInstacedRenerable = createInstancedRenderable(fish, Phong(Colour(0.0, 1.0, 1.0), LightPosition(2., 2., 15.)));
}


BoidsSimulation::BoidsSimulation()
{
  // Create some Boids
  for (int i = 0; i < numBoids; ++i) {
    float x = (random() % 4000) / 100.0f - 20.0f;
    float y = (random() % 4000) / 100.0f - 20.0f;
    float z = (random() % 4000) / 100.0f - 20.0f;
    
    float vx = (random() % 1000) / 10.0f - 50.f;
    float vy = (random() % 1000) / 10.0f - 50.f;
    float vz = (random() % 1000) / 10.0f - 50.f;

    boids.push_back(Boid(vec3(x,y,z), vec3(vx, vy, vz)));
  }
  
  auto fish = Mesh(Filename("../models/fish.obj"));
  
  // create the visual for the boid
  boidInstacedRenerable = createInstancedRenderable(fish, Phong(Colour(0.0, 1.0, 1.0), LightPosition(2., 2., 15.)));
}

BoidsSimulation::~BoidsSimulation()
{
  
}


float BoidsSimulation::basisFunction(float u, float uStart, float width, float shift)
{
  // 
  u = u - uStart;
  u = 3.0 * u / width;
  
  // Implements a 3rd order b-spline basis function (uniform knots)
  if (u < 0.0 - shift)
    return 0.0;
  else if (u < 1.0 - shift)
    return u * u / 2.0;
  else if (u < 2.0 - shift)
    return 3.0 / 4.0 - (u  - 3.0 / 4.0) * (u  - 3.0 / 4.0);
  else if (u < 3.0 - shift)
    return (3.0 - u) * (3.0 - u) / 2.0;
  
  return 0.0;
}


void BoidsSimulation::step(float timeStep)
{
  float dt = timeStep / (float) iterations;
  
  for (int iter = 0; iter < iterations; ++iter) {
    
    // Place the boids onto the grid
    for (int i = 0; i < numBoids; ++i) {
      grid.addBoidToGrid(i, boids[i].getPosition());
    }
    
    // Apply forces to the boids
    for (int i = 0; i < numBoids; ++i) {
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
          float k = 4.0;
          vec3 force = - k * (distance - avoidenceDistance) * direction;

          boids[i].applyForce(force);
        }
        // Cohesion forces
        else if (distance < cohesionDistance) {
          // apply a force to make the velocities match
          vec3 force = boids[j].getVelocity() - boids[i].getVelocity();
          force *= basisFunction(distance, avoidenceDistance, cohesionDistance - avoidenceDistance);

          boids[i].applyForce(force);
        }
        // Gathering forces
        else if (distance < gatheringDistance) {
          vec3 direction = normalize(boids[i].getPosition() - boids[j].getPosition());

          // attach a spring
          float k = 10.0;
          vec3 force = -k * (gatheringDistance - distance) * direction;
          force *= basisFunction(distance, cohesionDistance, gatheringDistance - cohesionDistance);

          boids[i].applyForce(force);
        }
      }
      
      // Force the boid towards the center
      vec3 pos = boids[i].getPosition();
      if (forceToCenter) {
        vec3 force = -pos * 0.4f;
        
        vec3 banking = vec3(0.0);
        if (length(pos) > 0.001)
          banking = cross(normalize(pos), -boids[i].getNormal());

        force += banking * 8.f;
        
        boids[i].applyForce(force);
      }

      // If too far away from the center
      if (length(pos) < maxDistanceFromOrigin)
        continue;
      
      vec3 force = 0.2f * -pos - 0.2f * boids[i].getVelocity();
      
      vec3 banking = cross(normalize(pos), boids[i].getNormal());
      
      force += banking * 2.f;
      
      boids[i].applyForce(force);
      
    }
    
    grid.tick();
    
    //move the boids
    for (int i = 0; i < numBoids; ++i) {
      boids[i].move(dt);
    }
  }
}

void BoidsSimulation::drawSimulation(const ViewContext<TurnTableCamera, PerspectiveProjection> &view)
{
  // Draw the boids
  for (int i = 0; i < (int)boids.size(); ++i) {
    mat4f transform = boids[i].getTransform();
    transform = scale(transform, boidScale);
    addInstance(boidInstacedRenerable, transform);
  }
  
  draw(boidInstacedRenerable, view);
}


