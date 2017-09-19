#ifndef PATHTRACER_H__
#define PATHTRACER_H__

#include <vector>
#include <memory>

#include "Scene.h"
#include "Sphere.h"
#include "Light.h"
#include "Image.h"

// PathTracer
namespace PT
{

enum RenderPass : unsigned char
{
  // TODO: Not all passes are vec3f
  Beauty,
  DirectDiffuse,
  DirectSpecular,
  IndirectDiffuse,
  IndirectSpecular,
  Depth,
  NormalWorld,
  NormalCamera,
  Shadow
};

struct Ray
{
  vec3f origin; // Ray origin
  vec3f direction; // Ray direction
};

struct RenderSettings
{
  float fieldOfView;

  int maxSamples;
  int maxPathLength;
  // Russian roulette
  int rouletteDepth;
  float rouletteThreshold;
};

/*
 *
 *  PathTracer
 *  Renders but does not have any display controls.
 *
 */
class PathTracer
{
public:
  PathTracer(int _width, int _height);
  ~PathTracer();

  // TODO: Switch these setTarget functions for a get function that returns color* to rendered data
  void setTarget(Image &_image); // this pixelBuffer is for display and PathTracer shouldn't care
  //void setTarget(const Image &_image); // this image is for display and PathTracer shouldn't care
  void getPass(const RenderPass _pass);

  // cropWindow decides which pixels should be sampled and should NOT interfere with size of pixelBuffers
  void cropWindow(const int _width, const int _height); // crops window with same centre as image
  void cropWindow(const int _xMin, const int _yMin, const int _xMax, const int _yMax); // corps window with min and max values
  // Renders to m_renderPasses
  void render();

private:
  // Scene data
  Sphere* m_spheres;
  int m_numSpheres;
  Light* m_lights;
  int m_numLights;
  // TODO: Use scene to store geometry, materials and handle intersections
  //Scene m_scene;

  // ImagePlane
  std::vector<Image*> m_renderPasses;
  Ray* m_rays;

  // Requested output image
  Image* m_outputImage;
  RenderPass m_outputPass;
  // At the end of each render cycle, image is exported
  void exportImage();

  // Render functions
  void tracePath(const int &_index, const int &_maxPathLength);
  float shadow(const vec3f &_ro, const vec3f &_rd);
  color getEnvironment(const vec3f &_direction);

  // TODO: Not used a.t.m.
  //std::vector<ushort> m_pixelSamples; // TODO: Do I need this? Perhaps for cropWindow changes!
  int m_samples;

  // TODO: To be removed
  vec3f m_groundNormal;
  vec3f m_groundPoint;
  //Image m_renderPass;
  std::vector<std::unique_ptr<Sphere>> m_primitives;
  //std::vector<std::unique_ptr<Light>> m_lights;
  float* m_image;
  float* m_image2;
};

} // namespace PT

#endif // PATHTRACER_H__
