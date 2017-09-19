#ifndef UTILITY_H__
#define UTILITY_H__

#include "math.h"

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

namespace PT
{

// TODO: Have a look at ngl::Util.h, ngl::Util.cpp and ngl::Types.h for global constants and functions


// Render settings
#define SAMPLES 128
#define TRACEDEPTH 4

// Calculations
#define EPSILON 0.0001f


// Common types and functions
// TODO: Isn't there an easier way to switch libraries after development?
// TODO: Looks like there is not :( so abort. This probably just slows down compilation. Just pick a library or make your own you lazy bastard.
typedef glm::vec2 vec2f;
typedef glm::vec3 vec3f;

#define _dot glm::dot
#define _cross glm::cross
#define _normalize glm::normalize
#define _pow glm::pow
#define _max glm::max




// Typedefs for better readability
typedef vec3f color;
// TODO: Decide wether pixel is (x,y) or (r,g,b) !!!
// TODO: Google it you idiot. It should be 2D, so fix it
typedef vec3f pixel;










} // namespace PT

#endif // UTILITY_H__

