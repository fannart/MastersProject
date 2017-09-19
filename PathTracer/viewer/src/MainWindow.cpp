#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "PathTraceWidget.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  std::cout << "MainWindow()" << std::endl;
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  std::cout << "~MainWindow()" << std::endl;
  delete ui;
}
