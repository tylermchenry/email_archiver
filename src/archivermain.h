#ifndef ARCHIVERMAIN_H
#define ARCHIVERMAIN_H

#include <QtGui/QMainWindow>
#include "ui_archivermain.h"
#include "archiver.h"

class ArchiverMain : public QMainWindow
{
    Q_OBJECT

public:
    ArchiverMain(QWidget *parent = 0);
    ~ArchiverMain();

private:
    Ui::ArchiverMainClass ui;
    Archiver archiver;
};

#endif // ARCHIVERMAIN_H
