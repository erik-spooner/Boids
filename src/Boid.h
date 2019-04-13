//
//

#ifndef Boid_h
#define Boid_h

#include <stdio.h>

#include "givr.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;
using namespace givr;
using namespace givr::style;
using namespace givr::geometry;
using namespace givr::camera;


class Boid
{
  vec3 position = vec3(0.0, 0.0, 0.0);
  vec3 velocity = vec3(0.0, 0.0, 0.0);
  vec3 force = vec3(0.0, 0.0, 0.0);
  
  vec3 tangent = vec3(1.0, 0.0, 0.0);
  vec3 normal = vec3(0.0, 1.0, 0.0);
  
  float mass = 1.0;
  
  const float maxVelocity = 20.0;
  const float minVelocity = 6.0;

public:
  
  Boid(vec3 initalPos, vec3 initialVel);
  ~Boid();
  
  // Updates the position, velocity and force from a semi implicit Euler's method
  void move(float dt);
  
  void applyForce(const vec3 appliedForce);
  
  vec3 getPosition() const;
  vec3 getVelocity() const;
  
  vec3 getNormal() const;
  
  mat4f getTransform() const;

};

#endif /* Boid_h */
