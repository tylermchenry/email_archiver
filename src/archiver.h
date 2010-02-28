#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QtGui/QDialog>
#include "ui_archiver.h"

class Archiver: public QDialog
{
  Q_OBJECT

  public:
    Archiver(QWidget *parent = 0);
    ~Archiver();

  public slots:

    void doTest();

  private:
    Ui::ArchiverClass ui;
};

#endif // ARCHIVER_H
