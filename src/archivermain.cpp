#include "archivermain.h"
#include <QtGui/QFileDialog>
#include "mboximporter.h"

ArchiverMain::ArchiverMain(QWidget *parent)
    : QMainWindow(parent)
{
  ui.setupUi(this);
  setCentralWidget(&archiver);

  statusBar()->addWidget(&prbProcessing, 1);
  prbProcessing.hide();

  statusBar()->showMessage("Ready");

  QMenu* fileMenu = new QMenu("File");
  loadAction = fileMenu->addAction("Import Email...");
  clearAction = fileMenu->addAction("Clear Data");
  fileMenu->addSeparator();
  exitAction = fileMenu->addAction("Exit");

  menuBar()->addMenu(fileMenu);

  connect(fileMenu, SIGNAL(triggered(QAction*)), this, SLOT(doAction(QAction*)));
}

ArchiverMain::~ArchiverMain()
{
}

void ArchiverMain::processingBegin()
{
  prbProcessing.setRange(0, 100);
  prbProcessing.reset();
  prbProcessing.show();
}

void ArchiverMain::processingProgress(int percent)
{
  prbProcessing.setValue(percent);
}

void ArchiverMain::processingEnd()
{
  prbProcessing.hide();
}

void ArchiverMain::doAction(QAction* action)
{
  if (action == loadAction) {
    loadEmail();
  } else if (action == clearAction) {
    archiver.clear();
    statusBar()->showMessage("Ready");
  } else if (action == exitAction) {
    this->destroy();
  }
}

void ArchiverMain::loadEmail()
{
  QString mboxFilename = QFileDialog::getOpenFileName
      (this, tr("Open MBox File"), "/home/tyler", tr("MBox Files (*.mbox)"));

  if (mboxFilename != "") {

    QFile mboxFile(mboxFilename);
    MBoxImporter importer;
    int messages;

    mboxFile.open(QIODevice::ReadOnly);

    processingBegin();

    connect(&importer, SIGNAL(progress(int)),
            this, SLOT(processingProgress(int)));

    connect(&importer, SIGNAL(newMessage(const MailMessage&)),
            &archiver, SLOT(addMessage(const MailMessage&)));

    archiver.clear();
    messages = importer.parse(mboxFile);

    disconnect(&importer, SIGNAL(newMessage(const MailMessage&)),
               &archiver, SLOT(addMessage(const MailMessage&)));

    disconnect(&importer, SIGNAL(progress(int)),
                this, SLOT(processingProgress(int)));

    processingEnd();

    statusBar()->showMessage("Loaded " + QString::number(messages) + " Messages");
  }
}
