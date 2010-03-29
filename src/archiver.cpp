#include "archiver.h"
#include "mboximporter.h"
#include <QMessageBox>
#include <QFileDialog>

Archiver::Archiver(QWidget *parent)
    : QDialog(parent), model(this)
{
  ui.setupUi(this);
  connect(ui.btnLoad, SIGNAL(clicked()), this, SLOT(doLoad()));
  ui.tblMessages->setModel(&model);
  ui.tblMessageDetails->setModel(&detailsModel);
  connect(&model, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
           ui.tblMessages, SLOT(scrollToBottom()));
  connect(&model, SIGNAL(messageSelected(const MailMessage&)),
           &detailsModel, SLOT(setMessage(const MailMessage&)));
  connect(ui.tblMessages->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),
          &model, SLOT(selectMessage(const QModelIndex&, const QModelIndex&)));
  connect(ui.btnClear, SIGNAL(clicked()), &model, SLOT(clear()));
  connect(ui.btnClear, SIGNAL(clicked()), &detailsModel, SLOT(clear()));
  connect(ui.btnClear, SIGNAL(clicked()), ui.prbProcessing, SLOT(reset()));
}

Archiver::~Archiver()
{

}

void Archiver::doLoad()
{
  QString mboxFilename = QFileDialog::getOpenFileName
      (this, tr("Open MBox File"), "/home/tyler", tr("MBox Files (*.mbox)"));

  if (mboxFilename != "") {
    QFile mboxFile(mboxFilename);
    MBoxImporter importer;

    mboxFile.open(QIODevice::ReadOnly);
    ui.prbProcessing->setEnabled(true);
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
    ui.prbProcessing->setEnabled(false);
  }
}

