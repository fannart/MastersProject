#ifndef PRIMITIVE_H__
#define PRIMITIVE_H__

#include "Utility.h"

namespace PT
{

class Primitive
{
public:
  Primitive();
  virtual ~Primitive() = 0;
  virtual bool intersect(const vec3f &_ro, const vec3f &_rd) const = 0;

private:
  // Material properties
  // Currently all primitives are purely diffuse
  // TODO: Make a seperate material class
  color albedo;
};


// TODO: All primitives should be derived from this class


} // namespace PT

#endif // PRIMITIVE_H__
