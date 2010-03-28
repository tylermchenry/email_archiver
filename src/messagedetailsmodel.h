/*
 * messagedetailsmodel.h
 * Part of email_archiver
 *
 *  Created on: Mar 28, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#ifndef MESSAGEDETAILSMODEL_H_
#define MESSAGEDETAILSMODEL_H_

#include <QObject>
#include <QAbstractTableModel>
#include "mailmessage.h"

class MessageDetailsModel : public QAbstractTableModel
{
  Q_OBJECT;

  public:

    MessageDetailsModel(QObject* parent = NULL);

    virtual ~MessageDetailsModel();

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                   int role = Qt::DisplayRole) const;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

  public slots:

    void clear();

    void setMessage(const MailMessage& message);

  private:

    MailMessage message;
};

#endif /* MESSAGEDETAILSMODEL_H_ */
