#ifndef ARCHIVERMAIN_H
#define ARCHIVERMAIN_H

#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include "ui_archivermain.h"
#include "archiver.h"

class ArchiverMain : public QMainWindow
{
    Q_OBJECT

  public:

    ArchiverMain(QWidget *parent = 0);
    ~ArchiverMain();

  public slots:

    void processingBegin();
    void processingProgress(int percent);
    void processingEnd();

    void doAction(QAction* action);

  private:

    Ui::ArchiverMainClass ui;
    Archiver archiver;
    QProgressBar prbProcessing;
    QAction* loadAction;
    QAction* clearAction;
    QAction* exitAction;

    void loadEmail();

};

#endif // ARCHIVERMAIN_H
