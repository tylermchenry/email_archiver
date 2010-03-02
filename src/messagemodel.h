/*
 * messagemodel.h
 * Part of email_archiver
 *
 *  Created on: Mar 1, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#ifndef MESSAGEMODEL_H_
#define MESSAGEMODEL_H_

#include <QObject>
#include <QAbstractTableModel>
#include "mailmessage.h"
#include <vector>

class MessageModel : public QAbstractTableModel
{
    Q_OBJECT

  public:

    MessageModel(QObject* parent = NULL);
    virtual ~MessageModel();

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                   int role = Qt::DisplayRole) const;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    void clear();

  public slots:

    void addMessage(const MailMessage& message);

  private:

    std::vector<MailMessage> messages;
};

#endif /* MESSAGEMODEL_H_ */
