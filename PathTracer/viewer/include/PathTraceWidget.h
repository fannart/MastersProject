#ifndef PATHTRACEWIDGET_H__
#define PATHTRACEWIDGET_H__

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QImage>
#include <QMouseEvent>

#include "PathTracer.h"
#include "Image.h"

class PathTraceWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
  PathTraceWidget(QWidget *_parent);
  ~PathTraceWidget();

  QSize minimumSizeHint() const Q_DECL_OVERRIDE;
protected:
  void initializeGL() Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void resizeGL(int _width, int _height) Q_DECL_OVERRIDE;
  void mousePressEvent(QMouseEvent *_event) Q_DECL_OVERRIDE;
  void mouseMoveEvent(QMouseEvent *) Q_DECL_OVERRIDE;
  void mouseReleaseEvent(QMouseEvent *) Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *_event) Q_DECL_OVERRIDE;
private:
  // Convert m_imageData to correct format for m_displayImage
  void convertToQImage();

  // Maximum size of widget and pixelBuffers of renderer
  const int m_maxWidth;
  const int m_maxHeight;
  // Current size of widget
  int m_currentWidth;
  int m_currentHeight;
  // PathTracer object for rendering
  PT::PathTracer m_pathTracer;
  // Image containing the pixelBuffer to be displayed
  PT::Image* m_imageData;
  // TODO: Use or not? could pass PT::RenderPass as argument to function instead
  // enum to select pass for display
  // PT::RenderPass m_displayPass;
  // QImage to be displayed after format conversion
  QImage m_displayImage;



  // TODO: Probably to be removed
  QImage m_imageToDisplay;

  float m_backgroundColor[3];

};

#endif // PATHTRACEWIDGET_H__
