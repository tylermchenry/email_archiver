#include <QtCore>
#include <QApplication>
#include "archivermain.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ArchiverMain mainWindow;

  mainWindow.show();

  return a.exec();
}
