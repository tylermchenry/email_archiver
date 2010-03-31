#include "archiver.h"

Archiver::Archiver(QWidget *parent)
    : QDialog(parent), model(this)
{
  ui.setupUi(this);
  ui.tblMessages->setModel(&model);
  ui.tblMessageDetails->setModel(&detailsModel);
  connect(&model, SIGNAL(rowsInserted(const QModelIndex&, int, int)),
           ui.tblMessages, SLOT(scrollToBottom()));
  connect(&model, SIGNAL(messageSelected(const MailMessage&)),
           &detailsModel, SLOT(setMessage(const MailMessage&)));
  connect(ui.tblMessages->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex&, const QModelIndex&)),
          &model, SLOT(selectMessage(const QModelIndex&, const QModelIndex&)));
}

Archiver::~Archiver()
{

}


void Archiver::addMessage(const MailMessage& message)
{
  model.addMessage(message);
}

void Archiver::clear()
{
  model.clear();
  detailsModel.clear();
}
