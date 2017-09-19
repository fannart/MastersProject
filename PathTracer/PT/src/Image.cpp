#include "Image.h"

#include <iostream>

namespace PT
{

Image::Image(int _width, int _height)
{
  std::cout << "Image()" << std::endl;
  m_width = _width;
  m_height = _height;
  m_buffer = new color[m_width * m_height];
  clear(color(0,0,0));
}

Image::~Image()
{
  std::cout << "~Image()" << std::endl;
  delete[] m_buffer;
}

void Image::clear(color _color)
{
  for(int i = 0; i < m_width * m_height; ++i)
  {
    m_buffer[i] = _color;
  }
}

int Image::getWidth() const
{
  return m_width;
}

int Image::getHeight() const
{
  return m_height;
}

uint Image::getPixel8BitRGB(int _x, int _y) const
{
  int index = _y * m_width + _x;
  uint r = (uint)(m_buffer[index].r * 255);
  uint g = (uint)(m_buffer[index].g * 255);
  uint b = (uint)(m_buffer[index].b * 255);
  if(r > 255) r = 255;
  if(g > 255) g = 255;
  if(b > 255) b = 255;
  return 0xff000000 | (r << 16) | (g << 8) | b;
}

void Image::gammaCorrect()
{
  // TODO: Overload function with gamma parameter
  // TODO: Do sRGB gamma
  for(int i = 0; i < m_width * m_height; ++i)
  {
    m_buffer[i].r = _pow(m_buffer[i].r, (float)1/2.2f);
    m_buffer[i].g = _pow(m_buffer[i].g, (float)1/2.2f);
    m_buffer[i].b = _pow(m_buffer[i].b, (float)1/2.2f);
  }
}

} // namespace PT
