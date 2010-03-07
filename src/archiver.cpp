#include "archiver.h"
#include "mboximporter.h"
#include <QMessageBox>
#include <QFileDialog>

Archiver::Archiver(QWidget *parent)
    : QDialog(parent), model(this)
{
  ui.setupUi(this);
  connect(ui.btnTest, SIGNAL(clicked()), this, SLOT(doTest()));
  ui.tblMessages->setModel(&model);
  connect(&model, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
           ui.tblMessages, SLOT(scrollToBottom()));
  connect(ui.btnClear, SIGNAL(clicked()), &model, SLOT(clear()));
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

    model.clear();
    importer.parse(mboxFile);

    disconnect(&importer, SIGNAL(newMessage(const MailMessage&)),
                &model, SLOT(addMessage(const MailMessage&)));

    disconnect(&importer, SIGNAL(progress(int)),
                ui.prbProcessing, SLOT(setValue(int)));

    ui.prbProcessing->setValue(100);
  }
}

