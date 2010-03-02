#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QtGui/QDialog>
#include "ui_archiver.h"
#include "messagemodel.h"

class Archiver: public QDialog
{
  Q_OBJECT

  public:
    Archiver(QWidget *parent = NULL);
    ~Archiver();

  public slots:

    void doTest();

  private:

    Ui::ArchiverClass ui;
    MessageModel model;
};

#endif // ARCHIVER_H
