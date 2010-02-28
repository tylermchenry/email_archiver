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
    mboxFile.open(QIODevice::ReadOnly);
    std::size_t messagesFound = MBoxImporter().parse(mboxFile);
    QMessageBox::information(this, "Email Archiver", "Found " + QString().setNum(messagesFound) +
                             " messages.");
  }
}
