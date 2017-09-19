#include "Sphere.h"

#include <utility>

#include <iostream>

namespace PT
{

Sphere::Sphere()
{

}

Sphere::Sphere(const vec3f &_center, const float &_radius)
{
  std::cout << "Sphere()" << std::endl;
  m_center = _center;
  m_radius = _radius;
}

// Citation start
// http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
// And the gmtl library
// TODO: Have a better look at the solution in the gmtl library
bool Sphere::intersect(const vec3f &_ro, const vec3f &_rd, float &o_dist) const
{
  // Assume _rd is normalized

  float t0, t1;
#if 0
  // Geometric solution
  // Find vector from sphere center to ray origin
  vec3f L = m_center - _ro;
  // Project L on _rd
  float tca = glm::dot(L, _rd);
  // tca is the distance from the ray origin to a line perpendicular to the center of the sphere
  // tca can be negative but there still be an intersection if ray origin is inside the sphere
  /*
  if(tca < 0)
  {
    return false;
  }
  */
  // TODO: Perhaps store radius2 as a member variable
  float radius2 = m_radius * m_radius;
  // d is perpendicular to tca and is the distance from the center of the sphere
  float d2 = radius2 - tca * tca;
  if(d2 > radius2)
  {
    return false;
  }
  float thc = sqrt(radius2 - d2);
  t0 = tca - thc;
  t1 = tca + thc;
#else
  // Analytic solution
  vec3f L = _ro - m_center;
  // Prepare to solve a quadratic equation
  // Since assuming _rd is normalized, a = 1
  float b = 2 * _dot(_rd, L);
  // TODO: Could store radius2 as a member variable
  float c = _dot(L, L) - m_radius * m_radius;
  // Solving the quadratic equation
  float discr = b * b - 4 * c;
  if(discr < 0)
  {
    return false;
  }
  // When ray intersects sphere in exactly one point
  else if(discr < EPSILON)
  {
    t0 = t1 = -0.5 * b;
  }
  else
  {
    float q = (b > 0) ?
          -0.5 * (b + sqrt(discr)) :
          -0.5 * (b - sqrt(discr));
    t0 = q;
    t1 = c / q;
  }
#endif
  if(t0 > t1)
  {
    std::swap(t0, t1);
  }
  if(t0 < 0)
  {
    t0 = t1;
    if(t0 < 0)
    {
      return false;
    }
  }

  o_dist = t0;
  return true;
}
// Citation end

}
