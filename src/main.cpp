#include <QtCore>
#include <QApplication>
#include "archiver.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Archiver mainDialog;

  mainDialog.show();

  return a.exec();
}
