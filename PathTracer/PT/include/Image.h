#ifndef IMAGE_H__
#define IMAGE_H__

#include "Utility.h"

namespace PT
{

class PathTracer;

class Image
{
  friend PathTracer;
public:
  Image(int _width, int _height);
  ~Image();
  void setPixel(int _index, const color &_color);
  void setPixel(int _x, int _y, const color &_color);
  void clear(color _color);
  int getWidth() const;
  int getHeight() const;
  uint getPixel8BitRGB(int _x, int _y) const;
  void gammaCorrect();
private:
  int m_width;
  int m_height;
  color* m_buffer;
};

} // namespace PT

#endif // IMAGE_H__
