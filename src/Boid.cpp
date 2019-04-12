//
//

#include "Boid.h"

Boid::Boid(vec3 initalPosition, vec3 initialVelocity)
{
  position = initalPosition;
  velocity = initialVelocity;
}


Boid::~Boid()
{
  
}


void Boid::move(float dt)
{
  // If there is enough force update the normal
  if (length(force) > 0.0001)
    normal = normalize(-force);
  
  // Update the velocity using
  // a = F / m
  velocity = velocity + dt * force / mass;
  
  // If the new velocity is big enough update the tangent
  if (length(velocity) > 0.0001)
    tangent = normalize(velocity);
  
  // clamp the velocity
  if (length(velocity) > maxVelocity)
    velocity = normalize(velocity) * maxVelocity;
  
  if (length(velocity) < minVelocity)
    velocity = normalize(velocity) * minVelocity;

  
  // Update the position using the new velocity
  position = position + dt * velocity;
  
  force = vec3(0.0);
}


void Boid::applyForce(const vec3 appliedForce)
{
  force += appliedForce;
  if (force != force)
    std::cout << "ahhh" << std::endl;
}


vec3 Boid::getPosition() const
{
  return position;
}

vec3 Boid::getVelocity() const
{
  return velocity;
}

vec3 Boid::getNormal() const
{
  return normal;
}


mat4f Boid::getTransform() const
{
  // B N T X
  
  vec3 binormal = normalize(cross(tangent, normal));
  if (binormal.x != binormal.x || binormal.y != binormal.y || binormal.z != binormal.z)
    binormal = vec3(1.0, 0.0, 0.0);
  
  vec3 modifiedTangent = normalize(cross(normal, binormal));
  
  mat4f transform = mat4f(1.0);
  
//  transform[0] = vec4(binormal, 0.0);
//  transform[1] = vec4(normal, 0.0);
//  transform[2] = vec4(modifiedTangent, 0.0);
  
  transform = translate(transform, position);

  return transform;
}
