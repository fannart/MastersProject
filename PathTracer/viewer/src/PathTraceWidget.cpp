#include "PathTraceWidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <QGuiApplication>

#include <iostream>

#include "Utility.h"

PathTraceWidget::PathTraceWidget(QWidget *_parent) :
  QOpenGLWidget(_parent),
  m_maxWidth(1000),
  m_maxHeight(500),
  m_pathTracer(m_maxWidth, m_maxHeight)
{
  std::cout << "PathTraceWidget()" << std::endl;
  m_backgroundColor[0] = 1;
  m_backgroundColor[1] = 1;
  m_backgroundColor[2] = 1;

  m_imageToDisplay = QImage(m_maxWidth, m_maxHeight, QImage::Format_RGB888);
  m_imageToDisplay.fill(QColor(0,0,0));

  m_imageData = new PT::Image(m_maxWidth, m_maxHeight);
  m_pathTracer.setTarget(*m_imageData);
  m_pathTracer.getPass(PT::Beauty);

  setFocusPolicy(Qt::StrongFocus);
}

PathTraceWidget::~PathTraceWidget()
{
  delete m_imageData;
}

QSize PathTraceWidget::minimumSizeHint() const
{
  std::cout << "minimumSizeHint()" << std::endl;
  return QSize(50, 50);
}

void PathTraceWidget::initializeGL()
{
  std::cout << "initializeGL()" << std::endl;
  initializeOpenGLFunctions();
}

void PathTraceWidget::paintGL()
{
  glClearColor(m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 1);
  glClear(GL_COLOR_BUFFER_BIT);

  m_pathTracer.render();

  // TODO: This function possibly slowing program down considerably
  convertToQImage();

  QPainter painter;
  painter.begin(this);
  // TODO: draw image with center at center of rect
  painter.drawImage(QRect(0, 0, m_maxWidth, m_maxHeight), m_imageToDisplay);
  painter.end();

  update();
}

void PathTraceWidget::convertToQImage()
{
  // TODO: Only convert pixels fitting within current widget size
//  switch(m_displayImage.format())
//  {
//  case QImage::Format_RGB888:
    for(int y = 0; y < m_maxHeight; ++y)
    {
      for(int x = 0; x < m_maxWidth; ++x)
      {
        uint color = m_imageData->getPixel8BitRGB(x, y);
        m_imageToDisplay.setPixel(x, y, color);
      }
    }
//    break;
//  }
}

void PathTraceWidget::resizeGL(int _width, int _height)
{
  std::cout << _width << " x " << _height << std::endl;
  m_currentWidth = _width;
  m_currentHeight = _height;

  update();
}

void PathTraceWidget::mousePressEvent(QMouseEvent *_event)
{
  std::cout << "mousePressEvent()" << std::endl;

  switch(_event->button())
  {
  case Qt::LeftButton:
    break;
  case Qt::RightButton:
    break;
  default:
    break;
  }

  update();
}

void PathTraceWidget::mouseMoveEvent(QMouseEvent *)
{
  std::cout << "mouseMoveEvent()" << std::endl;

  update();
}

void PathTraceWidget::mouseReleaseEvent(QMouseEvent *)
{
  std::cout << "mouseReleaseEvent()" << std::endl;

  update();
}

void PathTraceWidget::keyPressEvent(QKeyEvent *_event)
{
  std::cout << "PathTraceWidget - keyPressEvent() - " << _event->key() << std::endl;

  switch(_event->key())
  {
  case Qt::Key_Escape:
    QGuiApplication::exit(EXIT_SUCCESS);
    break;
  case Qt::Key_1:
    m_pathTracer.getPass(PT::Beauty);
    break;
  case Qt::Key_2:
    m_pathTracer.getPass(PT::DirectDiffuse);
    break;
  case Qt::Key_3:
    m_pathTracer.getPass(PT::IndirectDiffuse);
    break;
  case Qt::Key_4:
    m_pathTracer.getPass(PT::DirectSpecular);
    break;
  case Qt::Key_5:
    m_pathTracer.getPass(PT::IndirectSpecular);
    break;
  case Qt::Key_6:
    m_pathTracer.getPass(PT::Depth);
    break;
  case Qt::Key_7:
    m_pathTracer.getPass(PT::NormalWorld);
    break;
  case Qt::Key_8:
    m_pathTracer.getPass(PT::NormalCamera);
    break;
  }

  update();
}
