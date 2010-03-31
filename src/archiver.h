#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <QtGui/QDialog>
#include "ui_archiver.h"
#include "messagemodel.h"
#include "messagedetailsmodel.h"

class Archiver: public QDialog
{
  Q_OBJECT

  public:
    Archiver(QWidget *parent = NULL);
    ~Archiver();

  public slots:

    void addMessage(const MailMessage& message);
    void clear();

  private:

    Ui::ArchiverClass ui;
    MessageModel model;
    MessageDetailsModel detailsModel;
};

#endif // ARCHIVER_H
