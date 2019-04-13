//
//

#ifndef BoidsSimulation_h
#define BoidsSimulation_h

#include <stdio.h>
#include <vector>

#include "Boid.h"
#include "Grid.h"

using namespace glm;
using namespace givr;
using namespace givr::camera;
using namespace givr::geometry;
using namespace givr::style;

class BoidsSimulation {
  std::vector<Boid> boids;
  
  PhongStyle::InstancedRenderContext boidInstacedRenerable;
  
  const int numBoids = 7500;
  const int iterations = 1;
  
  const float avoidenceDistance = 1;
  const float cohesionDistance = 3;
  const float gatheringDistance = 5;
  const float maxDistanceFromOrigin = 40.0;
  
  
  const int gridSize = 50;
  const float cellWidth = gatheringDistance / 4.0f;
  
  
  const vec3 boidScale = vec3(0.175);
  
  Grid grid = Grid(gridSize, cellWidth);
  
  float basisFunction(float u, float uStart, float width, float shift = 0.0);
  
public:
  
  BoidsSimulation(int nB, float aD, float cD, float gD, int iters);
  BoidsSimulation();
  ~BoidsSimulation();
  
  bool forceToCenter = false;
  
  void step(float dt);
  void drawSimulation(const ViewContext<TurnTableCamera, PerspectiveProjection> &view);
  
  
};

#endif /* BoidsSimulation_h */
