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
  
  const float avoidenceDistance = 3.0;
  const float cohesionDistance = 9.0;
  const float gatheringDistance = 20.0;
  const float maxDistanceFromOrigin = 100.0;
  
  const int iterations = 1;
  
  Grid grid;
  
public:
  
  BoidsSimulation();
  ~BoidsSimulation();
  
  void step(float dt);
  void drawSimulation(const ViewContext<TurnTableCamera, PerspectiveProjection> &view);
  
  
};

#endif /* BoidsSimulation_h */
