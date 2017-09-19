#ifndef LIGHT_H__
#define LIGHT_H__

#include "Utility.h"

namespace PT {

class Light
{
public:
  Light();

  float m_intensity;
};

// TODO: Try to place a PointLight in a std::vector of Light
class PointLight : Light
{

};

} // namespace PT

#endif // LIGHT_H__
