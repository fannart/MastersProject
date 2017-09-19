#ifndef SCENE_H__
#define SCENE_H__

#include "Utility.h"

#include <vector>

#include "Sphere.h"

namespace PT
{

struct Plane
{
  float distanceFromOrigin;
  vec3f normal;
};

/*
 *
 *  Scene
 *  Should only be an interface to create the scene
 *
 */
class Scene
{
public:
  Scene();
  void setBackground(color _color);
  color getBackground(const color &_rayDirection) const;
  // TODO: Set correct parameters
  void addPlane(const float &_distanceFromOrigin, const vec3f &_normal = vec3f(0,1,0));
  void addSphere(const float &_radius, const vec3f &_center);
private:
  color m_backgroundColor;
  // TODO: Preferably keep all primitives in same vector?
  std::vector<Plane*> m_planes;
  std::vector<Sphere*> m_spheres;
};

} // namespace PT

#endif // SCENE_H__
