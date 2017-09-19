#include <QApplication>
#include <QSurfaceFormat>

#include "MainWindow.h"

#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "main()" << std::endl;
  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow w;
  w.show();

  return a.exec();
}
