#include "PathTracer.h"

#include <iostream>
#include <random>

#include "Sphere.h"

namespace PT
{

// TODO: Find a place for math in a cpp file
// TODO: What else belongs in this namespace...constants, functions


// Random functions
std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0, 1);
// TODO: Passing data around? Parameters and return value
vec3f randomUniformHemisphereSample(vec3f &_normal)
{
  // TODO: This sampling needs to be checked!
  // TODO: It appears that the samples generated are
  float r1 = distribution(generator);
  float r2 = distribution(generator);

  // Generate sample
  // y = cosTheta = _ri
  float sinTheta = sqrt(1 - r1 * r1);
  // TODO: Const for M_2PI
  float phi = 2 * M_PI * r2;
  float x = sinTheta * cosf(phi);
  float z = sinTheta * sinf(phi);
  vec3f sample = vec3f(x, r1, z);

  // TODO: Remove. For testing only. Sets the sample as the normal.
  //sample = vec3f(0,1,0);

  // Transform sample around normal
  // Transformation corrected, checked and confirmed correct
  vec3f Nt;
  // TODO: Make sqrt(1/3) a constant
  //if(abs(_normal.x) < sqrt(1/3))


  // This creates a problem when x is close to y
  /*
  if(_normal.x > _normal.y)
  {
    Nt = vec3f(-_normal.z, 0, _normal.x);
  }
  else
  {
    Nt = vec3f(0, -_normal.z, _normal.y);
  }
  */
  /*
  vec3f shortAxis;
  // TODO: Make sqrt(1/3) a constant
  // TODO: This creates render artifacts when _normal.y is close to sqrt(1.0f/3)
  if(fabs(_normal.y) < sqrt(1.0f/3))
  {
    shortAxis = vec3f(0,1,0);
  }
  else if(fabs(_normal.x) < sqrt(1.0f/3))
  {
    shortAxis = vec3f(1,0,0);
  }
  else
  {
    shortAxis = vec3f(0,0,1);
  }


  // The _normal, Nt and Nb should form 3 orthogonal axis
  // Nt should be orthogonal to the _normal
  Nt = _cross(_normal, shortAxis);
  */

  // All the following: choice of Nt, order of cross product and
  // arrangement in final matrix multiplication combine
  // to a right/left handed coordinate system.
  // This renderer uses right-handed.

  // Calculate Nt based on the values in _normal
  if(fabs(_normal.x) > fabs(_normal.y))
  {
    Nt = vec3f(_normal.z, 0, -_normal.x);
  }
  else
  {
    Nt = vec3f(0, -_normal.z, _normal.y);
  }

  // TODO: Since we know one axis is zero the normalization could be simplified
  Nt = _normalize(Nt);
  // Nb should be orthogonal to the _normal and Nt
  vec3f Nb = _cross(_normal, Nt);

  // sample * 3x3 transformation matrix
  vec3f newSample = vec3f(sample.x * Nt.x + sample.y * _normal.x + sample.z * Nb.x,
               sample.x * Nt.y + sample.y * _normal.y + sample.z * Nb.y,
               sample.x * Nt.z + sample.y * _normal.z + sample.z * Nb.z);
//  if(_dot(Nb, Nb) < 0.55)
//  {
//    std::cout << _dot(Nb, Nb) << std::endl;
//    std::cout << "N:  ("
//              << _normal.x << ",\t "
//              << _normal.y << ",\t "
//              << _normal.z << ") " << std::endl;
//    std::cout << "Nt: ("
//              << Nt.x << ",\t "
//              << Nt.y << ",\t "
//              << Nt.z << ") " << std::endl;
//    std::cout << "Nb: ("
//              << Nb.x << ",\t "
//              << Nb.y << ",\t "
//              << Nb.z << ") " << std::endl;
//    std::cout << "Sample: ("
//              << sample.x << ", "
//              << sample.y << ", "
//              << sample.z << ")" << std::endl;
//    std::cout << "Sample: ("
//              << newSample.x << ", "
//              << newSample.y << ", "
//              << newSample.z << ")" << std::endl;
//  }
  // Will give an error message if generated sample is not in the hemisphere around the normal
//  if(_dot(newSample, _normal) < 0)
//  {
//    std::cout << "ERROR: Sample is not in hemisphere!" << std::endl;
//    std::cout << "N:  ("
//              << _normal.x << ",\t "
//              << _normal.y << ",\t "
//              << _normal.z << ") " << std::endl;
//    std::cout << "Nt: ("
//              << Nt.x << ",\t "
//              << Nt.y << ",\t "
//              << Nt.z << ") " << std::endl;
//    std::cout << "Nb: ("
//              << Nb.x << ",\t "
//              << Nb.y << ",\t "
//              << Nb.z << ") " << std::endl;
//    std::cout << "Sample: ("
//              << sample.x << ", "
//              << sample.y << ", "
//              << sample.z << ")" << std::endl;
//    std::cout << "Sample: ("
//              << newSample.x << ", "
//              << newSample.y << ", "
//              << newSample.z << ")" << std::endl;
//  }
  // TODO: Check if newSample is normalized
  if(_dot(newSample, newSample) > 1 + 0.0001f)
  {
    std::cout << "ERROR: newSample is not normalized : " << _dot(newSample, newSample) << std::endl;
  }
  return newSample;
}


/*
 *
 *  PathTracer
 *  TODO: Should constructor take these parameters?
 *  TODO: Perhaps a Image and Scene references would make more sense?
 *
 */

PathTracer::PathTracer(int _width, int _height)
{
  std::cout << "PathTracer()" << std::endl;

  m_groundNormal = vec3f(0,1,0);
  m_groundPoint = vec3f(0,-1.5,0);

  // TODO: Keep one pixelBuffer for accumulated samples and another for averages
  // TODO: Scratch that. Just average on export. Duhhh
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));
  m_renderPasses.push_back(new Image(_width, _height));


  // TODO: Initialization of scene should be done outside PathTracer
  m_numSpheres = 4;
  m_spheres = new Sphere[m_numSpheres];

  m_spheres[0].m_center = vec3f(-2.2, -0.5, -8);
  m_spheres[0].m_radius = 1;
  m_spheres[0].m_color = color(0.9, 0.2, 0.2);
  //m_spheres[0].m_color = color(0.8, 0.8, 0.8);


  m_spheres[1].m_center = vec3f(0, -0.5, -8.5);
  m_spheres[1].m_radius = 1;
  m_spheres[1].m_color = color(0.2, 0.9, 0.2);
  //m_spheres[1].m_color = color(1, 1, 1);


  m_spheres[2].m_center = vec3f(2.2, -0.5, -8);
  m_spheres[2].m_radius = 1;
  m_spheres[2].m_color = color(0.2, 0.2, 0.9);
  //m_spheres[2].m_color = color(0.8, 0.8, 0.8);


  m_spheres[3].m_center = vec3f(-10, -1.5, -8);
  m_spheres[3].m_radius = 1;
  m_spheres[3].m_color = color(0.4, 0.4, 0.4);
  m_spheres[3].m_color = color(0.9, 0.9, 0.9);


  // TODO: Resize m_renderPasses. Hmmm
  m_image = new float[_width*_height*3];
  for(int i = 0; i < _width*_height; ++i)
  {
    m_image[3*i+0] = 0;
    m_image[3*i+1] = 0;
    m_image[3*i+2] = 0;
  }
  m_image2 = new float[_width*_height*3];
  for(int i = 0; i < _width*_height; ++i)
  {
    m_image2[3*i+0] = 0;
    m_image2[3*i+1] = 0;
    m_image2[3*i+2] = 0;
  }

  // A ray for every pixel
  m_rays = new Ray[1000*500];

  // TODO: Make array?
  m_samples = 0;
}

PathTracer::~PathTracer()
{
  std::cout << "~PathTracer()" << std::endl;
  delete[] m_image;
  delete[] m_image2;
  delete[] m_rays;
  delete[] m_spheres;
  std::cout << "m_renderPasses.size() = " << m_renderPasses.size() << std::endl;
  for(unsigned int i = 0; i < m_renderPasses.size(); ++i)
  {
    delete m_renderPasses[i];
  }
  // TODO: Make sure all pointers are deleted
}

void PathTracer::setTarget(Image &_image)
{
  m_outputImage = &_image;
}

void PathTracer::render()
{
  std::cout << "render()" << std::endl;

  // Increase sample count
  // TODO: Consider having this for each pixel for change in cropWindow
  ++m_samples;
  std::cout << "m_samples : " << m_samples << std::endl;

  // TODO: Where do m_passes get their size? This should initialize imageWidth and imageHeight as well.
  // TODO: Make sure m_passes.data() exists!
  int imageWidth = 1000; //m_renderPasses.data()->getWidth();
  int imageHeight = 500; //m_renderPasses.data()->getHeight();
  float imageAspectRatio = (float)imageWidth / imageHeight;
  // TODO: Use cropWindow to determine min/Max pixel coordinates
  int xMin = 0;
  int xMax = imageWidth;
  int yMin = 0;
  int yMax = imageHeight;
  // For every pixel to be rendered
  float xJitter = distribution(generator);
  float yJitter = distribution(generator);
  for(int j = yMin; j < yMax; ++j)
  {
    for(int i = xMin; i < xMax; ++i)
    {
      int pixelIndex = j * imageWidth + i;
      // TODO: Implement
      // TODO: Get camera position and orientation
      // For now, assume static camera at 0,0,0 with view direction 0,0,-1
      vec3f cameraPosition = vec3f(0,0,0);
      //vec3f cameraViewDirection = vec3f(0,0,-1); // Used to calculate horizontal and vertical directions of the imageplane for a dynamic camera
      float cameraFOV = 30;

      // TODO: Generate ray through (x, y)
      // x and y are top-left corner of pixel in world space
      // TODO: Implement quasi monte carlo sampling
      // TODO: Can be simplified. For instance, there is no need to calculate tan for every pixel/ray
      float x = (2 * (((float)i + xJitter) / imageWidth) - 1) * imageAspectRatio * tan(cameraFOV * 0.5 * (M_PI / 180));
      float y = (1 - 2 * (((float)j + yJitter) / imageHeight)) * tan(cameraFOV * 0.5 * (M_PI / 180));
      vec3f rayOrigin = cameraPosition;
      vec3f pointOnImagePlane = vec3f(x, y, -1);
      vec3f rayDirection = _normalize(pointOnImagePlane - rayOrigin);
      m_rays[pixelIndex].origin = rayOrigin;
      m_rays[pixelIndex].direction = rayDirection;


      // TODO: Calculate color from ray non-recursively
      tracePath(pixelIndex, 10);

    }
  }
  exportImage();
}

// Citation starts
// Karl's and Peter's...
// TODO: What is from theirs
color backgroundColor(const vec3f &_direction)
{
  float position = (_dot(_direction, _normalize(vec3f(-0.5, 0.5, -1.0))) + 1) / 2;
  position = (_dot(_direction, _normalize(vec3f(1, 1, 0.5)))+1) / 2;
  // TODO: Select better colors. Consider Kelvin to rgb function
  color coldColor = color(0.04, 0.2, 0.47);   // Cold
  color warmColor = color(1.0, 0.7, 0.47);    // Warm
  // TODO: Decide on color for environment light
//  coldColor = color(0.01f, 0.01f, 0.01f);   // Cold
//  warmColor = color(1.0f, 1.0f, 1.0f);    // Warm

  color interpolatedColor = (1 - position) * coldColor + position * warmColor;
  float radianceMultiplier = 1.0;
  return interpolatedColor * radianceMultiplier;
}
// Citation ends

void PathTracer::tracePath(const int &_index, const int &_maxPathLength)
{
  /*
   *
   *  Iterative approach so process can be parallelized
   *
   */

  // Calculates path and radiance for pixel-path
  color unabsorbedAlbedo = color(1,1,1);
  color accumulatedRadiance = color(0,0,0);

  for(int p = 0; p < _maxPathLength; ++p)
  {
    // TODO: Place background color in function
    float d = (m_rays[_index].direction.x + m_rays[_index].direction.y) * 0.5f + 0.5f;
    color backgroundRadiance = color(d,d,d);
    backgroundRadiance = backgroundColor(m_rays[_index].direction);
    // TODO: Find closest intersection in scene
    int sphereIndex = -1;
    float hitDistance = 10000; // TODO: Should be infinity/floatMax
    // Intersect scene
    // TODO: Implement intersect functions outside of sphere class
    // TODO: Have that function take a sphere and ray references, in case of sphere

    // Intersect plane
    {
      // Assuming unit vectors
      // Plane defined with two vectors, could be vector and float

      float LdotN = _dot(m_groundNormal, m_rays[_index].direction);
      if(fabs(LdotN) > 0.001f) // TODO: Use a EPSILON constant
      {
        float t = _dot((m_groundPoint - m_rays[_index].origin), m_groundNormal) / LdotN;
        if (t > 0)
        {
          hitDistance = t;
          sphereIndex = -2;  // TODO: Quick fix to assign a material to plane. Should be fixed!
        }
      }
    }

    // Intersect spheres
    for(int i = 0; i < m_numSpheres; ++i)
    //for(int i = 0; i < m_primitives.size(); ++i)
    {
      // TODO: Should this variable be declared outside the loop?
      float distance = 100000;
      // TODO: Place geometry in scene class?
      if(m_spheres[i].intersect(m_rays[_index].origin, m_rays[_index].direction, distance) && distance < hitDistance)
      //if(m_primitives[i]->intersect(m_rays[_index].origin, m_rays[_index].direction, distance) && distance < hitDistance)
      {
        sphereIndex = i;
        hitDistance = distance;
      }
    }
    // If ray did not intersect any object in scene
    // TODO: This if statement should be eliminated once scene class is used
    if(hitDistance >= 10000)
    {
      // Return background "color" when first ray does not intersect any object
      // TODO: Sample environment light, if there is one. Possibly place in function.
      if(p == 0)
      {
        // TODO: Add background color
        // TODO: Consider alpha channel
        accumulatedRadiance += backgroundRadiance;// backgroundColor(m_rays[_index].direction);
        break;
      }
      else
      {
        break;
      }
    }
    else
    {
      // TODO: Setting material of plane. To be changed!
      // TODO: Object should contain material (index OR pointer) for material list within (scene OR renderer)
      if(sphereIndex == -2) sphereIndex = 3;


      // Get point of intersection and normal
      vec3f pointOfIntersection = m_rays[_index].origin + m_rays[_index].direction * hitDistance;
      vec3f surfaceNormal = _normalize(pointOfIntersection - m_spheres[sphereIndex].m_center);



      // TODO: Setting normal of plane. To be changed!
      if(sphereIndex == 3) surfaceNormal = m_groundNormal;
      // TODO: Could the surfaceNormal be on the other side of the surface?


      // TODO: Shading functions should be seperated out of here, or should they?

      // Get surface color
      // TODO: Should also work for other object types. Store materials separately.
      color surfaceColor = m_spheres[sphereIndex].m_color;

      // Compute direct lighting
      // TODO: For each light
            // TODO: Sample light and calculate contribution based on light direction, normal and light intensity
      // TODO: Sample lights. Don't forget to multiply result with cos(theta) and devide by sample pdf
      // TODO: This should be done by sampling lights in the scene.
      // TODO: For now, only send sample along normal.
      color localLighting = color(1,1,1);
      float NdotL;
      float worldShadow;

      {
        // TODO: Importance sampling for light direction. Cosine weighted and skip NdotL
        // TODO: Transformation to local space is done twice, once for light, once for next ray
        vec3f lightSampleDirection = randomUniformHemisphereSample(surfaceNormal);
        color lightSampleColor = backgroundRadiance;
        lightSampleColor = backgroundColor(lightSampleDirection);
        // TODO: Remove. For testing only.
        //lightSampleColor = backgroundColor(surfaceNormal);
        NdotL = _max(0.0f, _dot(lightSampleDirection, surfaceNormal));

        // Check intersection with scene for shadow ray
        // TODO: Use EPSILON constant
        worldShadow = shadow(pointOfIntersection + surfaceNormal * 0.0001f, lightSampleDirection);
        //worldShadow = shadow(pointOfIntersection + surfaceNormal * 0.0001f, surfaceNormal);

        localLighting = worldShadow * NdotL * lightSampleColor;
        // TODO: Remove. For testing only.
        //localLighting *= worldShadow;
      }

      // Prepare ray for next iteration
      // TODO: Calculate direction based on the local BRDF
      m_rays[_index].direction = randomUniformHemisphereSample(surfaceNormal);
      // TODO: Remove. For testing only.
      //m_rays[_index].direction = surfaceNormal;
//      std::cout << surfaceNormal.x << ", "
//                << surfaceNormal.y << ", "
//                << surfaceNormal.z << " : "
//                << m_rays[_index].direction.x << ", "
//                << m_rays[_index].direction.y << ", "
//                << m_rays[_index].direction.z << ": \t\t"
//                << "\t" << _dot(surfaceNormal, m_rays[_index].direction) << std::endl;
      // TODO: Use constant for EPSILON value
      m_rays[_index].origin = pointOfIntersection + surfaceNormal * 0.0001f;



      // TODO: Should the albedo not be divided by pi somewhere?
      unabsorbedAlbedo *= surfaceColor;
      accumulatedRadiance += unabsorbedAlbedo * localLighting;

      // Add radiance to corresponding renderPass
      if(p == 0)
      {
        m_renderPasses[RenderPass::DirectDiffuse]->m_buffer[_index] += accumulatedRadiance;
        // TODO: No need for an abundance of samples
        m_renderPasses[RenderPass::NormalWorld]->m_buffer[_index] += surfaceNormal * 0.5f + 0.5f;
      }
      else
      {
        m_renderPasses[RenderPass::IndirectDiffuse]->m_buffer[_index] += unabsorbedAlbedo * localLighting;
      }
    }
  }
  // TODO: This is the wrong buffer at the moment. Should be in m_renderPasses
  // TODO: Should add color to pixelBuffer, not setting
  // TODO: Should probably collect color samples of path and combine before doing anything with the pixelBuffer
  // TODO: Should be a color*
  m_image2[3 * _index + 0] += accumulatedRadiance.r;
  m_image2[3 * _index + 1] += accumulatedRadiance.g;
  m_image2[3 * _index + 2] += accumulatedRadiance.b;
  // Average samples
  // Gamma correct
//  m_image[3 * _index + 0] = pow(m_image2[3 * _index + 0] / m_samples, (float)1/2.2f);
//  m_image[3 * _index + 1] = pow(m_image2[3 * _index + 1] / m_samples, (float)1/2.2f);
//  m_image[3 * _index + 2] = pow(m_image2[3 * _index + 2] / m_samples, (float)1/2.2f);
  m_renderPasses[RenderPass::Beauty]->m_buffer[_index].r = m_image2[3 * _index + 0];
  m_renderPasses[RenderPass::Beauty]->m_buffer[_index].g = m_image2[3 * _index + 1];
  m_renderPasses[RenderPass::Beauty]->m_buffer[_index].b = m_image2[3 * _index + 2];
}

float PathTracer::shadow(const vec3f &_ro, const vec3f &_rd)
{
  // Intersect scene
  Ray ray;
  ray.origin = _ro;
  ray.direction = _rd;

  // Intersect plane
  {
    // Assuming unit vectors
    // Plane defined with two vectors, could be vector and float

    float LdotN = _dot(m_groundNormal, ray.direction);
    if(fabs(LdotN) > 0.0001f) // TODO: Use a EPSILON constant
    {
      float t = _dot((m_groundPoint - ray.origin), m_groundNormal) / LdotN;
      if (t > 0)
      {
        return 0;
      }
    }
  }

  // Intersect spheres
  for(int i = 0; i < m_numSpheres; ++i)
  //for(int i = 0; i < m_primitives.size(); ++i)
  {
    // TODO: Should this variable be declared outside the loop?
    float distance = 100000;
    // TODO: Place geometry in scene class?
    if(m_spheres[i].intersect(ray.origin, ray.direction, distance) && distance > 0)
    //if(m_primitives[i]->intersect(m_rays[_index].origin, m_rays[_index].direction, distance) && distance < hitDistance)
    {
      return 0;
    }
  }
  // Nothing intersected
  return 1;
}

void PathTracer::getPass(const RenderPass _pass)
{
  std::cout << "getPass() - " << _pass << std::endl;
  m_outputPass = _pass;
}

void PathTracer::exportImage()
{
  for(int i = 0; i < m_outputImage->getWidth() * m_outputImage->getHeight(); ++i)
  {
    m_outputImage->m_buffer[i].r = m_renderPasses[m_outputPass]->m_buffer[i].r / m_samples;
    m_outputImage->m_buffer[i].g = m_renderPasses[m_outputPass]->m_buffer[i].g / m_samples;
    m_outputImage->m_buffer[i].b = m_renderPasses[m_outputPass]->m_buffer[i].b / m_samples;
  }
  switch(m_outputPass)
  {
  case RenderPass::Beauty:
  case RenderPass::DirectDiffuse:
  case RenderPass::IndirectDiffuse:
  case RenderPass::DirectSpecular:
  case RenderPass::IndirectSpecular:
    m_outputImage->gammaCorrect();
    break;
  case RenderPass::Depth:
  case RenderPass::NormalWorld:
  case RenderPass::NormalCamera:
  case RenderPass::Shadow:
  default:
    std::cout << "No gamma correct on m_outputImage" << std::endl;
    break;
  }
}

} // namespace PT
