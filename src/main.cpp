//------------------------------------------------------------------------------
// A simple example showing how to use the triangle geometry
//------------------------------------------------------------------------------
#include "givr.h"
#include <glm/gtc/matrix_transform.hpp>

#include "io.h"
#include "turntable_controls.h"

#include "BoidsSimulation.h"

using namespace glm;
using namespace givr;
using namespace givr::camera;
using namespace givr::geometry;
using namespace givr::style;

int main(void)
{
  io::GLFWContext windows;
  auto window = windows.create(io::Window::dimensions{1280, 960}, "Boids");
  window.enableVsync(true);

  auto view = View(TurnTable(), Perspective());
  TurnTableControls controls(window, view.camera);

  BoidsSimulation simulation;
  
  glClearColor(1.f, 1.f, 1.f, 1.f);
  
  window.run([&](float frameTime) {
    view.projection.updateAspectRatio(window.width(), window.height());
    
    simulation.step(1.0 / 60.0);
    simulation.drawSimulation(view);
  });
  exit(EXIT_SUCCESS);
}


