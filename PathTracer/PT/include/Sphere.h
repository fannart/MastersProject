#ifndef SPHERE_H
#define SPHERE_H

#include "Utility.h"

namespace PT
{

class Sphere
{
public:
  Sphere();
  Sphere(const vec3f &_center, const float &_radius);
  bool intersect(const vec3f &_ro, const vec3f &_rd, float &o_dist) const;

  vec3f m_center;
  float m_radius;

  // TODO: Use Material properties instead
  // TODO: Have function return NORMAL
  vec3f m_color;
};

} // namespace PT

#endif // SPHERE_H
