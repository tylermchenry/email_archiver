#include "archiver.h"
#include "mboximporter.h"
#include <QMessageBox>
#include <QFileDialog>

Archiver::Archiver(QWidget *parent)
    : QDialog(parent)
{
  ui.setupUi(this);
  connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(doTest()));
}

Archiver::~Archiver()
{

}

void Archiver::doTest()
{
  QString mboxFilename = QFileDialog::getOpenFileName
      (this, tr("Open MBox File"), "/home/tyler", tr("MBox Files (*.mbox)"));

  if (mboxFilename != "") {
    QFile mboxFile(mboxFilename);
    MBoxImporter importer;

    mboxFile.open(QIODevice::ReadOnly);
    ui.prbProcessing->setRange(0, 100);
    ui.prbProcessing->reset();

    connect(&importer, SIGNAL(progress(int)), ui.prbProcessing, SLOT(setValue(int)));

    std::size_t messagesFound = importer.parse(mboxFile);

    disconnect(&importer, SIGNAL(progress(int)), ui.prbProcessing, SLOT(setValue(int)));

    ui.prbProcessing->setValue(100);

    QMessageBox::information(this, "Email Archiver", "Found " + QString().setNum(messagesFound) +
                             " messages.");
  }
}
