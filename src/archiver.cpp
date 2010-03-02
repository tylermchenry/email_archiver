#include "archiver.h"
#include "mboximporter.h"
#include <QMessageBox>
#include <QFileDialog>

Archiver::Archiver(QWidget *parent)
    : QDialog(parent), model(this)
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

    connect(&importer, SIGNAL(progress(int)),
             ui.prbProcessing, SLOT(setValue(int)));

    connect(&importer, SIGNAL(newMessage(const MailMessage&)),
             &model, SLOT(addMessage(const MailMessage&)));

    importer.parse(mboxFile);

    disconnect(&importer, SIGNAL(newMessage(const MailMessage&)),
                &model, SLOT(addMessage(const MailMessage&)));

    disconnect(&importer, SIGNAL(progress(int)),
                ui.prbProcessing, SLOT(setValue(int)));

    ui.prbProcessing->setValue(100);
    ui.tblMessages->setModel(&model);
  }
}

