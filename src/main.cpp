//------------------------------------------------------------------------------
// A simple example showing how to use the triangle geometry
//------------------------------------------------------------------------------
#include "givr.h"
#include <glm/gtc/matrix_transform.hpp>

#include "io.h"
#include "turntable_controls.h"

#include "BoidsSimulation.h"

#include "nlohmann/json.hpp"
#include <iostream>

using namespace glm;
using namespace givr;
using namespace givr::camera;
using namespace givr::geometry;
using namespace givr::style;


BoidsSimulation* loadSimulation(std::string file);

int main(void)
{
  io::GLFWContext windows;
  auto window = windows.create(io::Window::dimensions{1280, 960}, "Boids");
  window.enableVsync(true);

//  BoidsSimulation* simulation = new BoidsSimulation();
  BoidsSimulation* simulation = loadSimulation("../models/Scene.json");
  
  auto view = View(TurnTable(), Perspective());
  TurnTableControls controls(window, view.camera, simulation);
  
  glClearColor(1.f, 1.f, 1.f, 1.f);
    
  window.run([&](float frameTime) {
    view.projection.updateAspectRatio(window.width(), window.height());
    
    simulation->step(1.0 / 60.0);
    simulation->drawSimulation(view);
  });
  
  delete simulation;
  exit(EXIT_SUCCESS);
}


BoidsSimulation* loadSimulation(std::string file)
{
  nlohmann::json sceneDescription;
  std::ifstream in(file);
  in >> sceneDescription;
  in.close();
  
  int numBoids = sceneDescription.at("numBoids").get<int>();
  int numIterations = sceneDescription.at("numIterations").get<int>();
  
  int avoidenceDistance = sceneDescription.at("avoidenceDistance").get<float>();
  int cohesionDistance = sceneDescription.at("cohesionDistance").get<float>();
  int gatheringDistance = sceneDescription.at("gatheringDistance").get<float>();

  return new BoidsSimulation(numBoids, avoidenceDistance, cohesionDistance, gatheringDistance, numIterations);
}





