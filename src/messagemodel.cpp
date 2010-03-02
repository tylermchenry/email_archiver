/*
 * messagemodel.cpp
 * Part of email_archiver
 *
 *  Created on: Mar 1, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#include "messagemodel.h"

MessageModel::MessageModel(QObject* parent)
  : QAbstractTableModel(parent)
{
  // TODO Auto-generated constructor stub

}

MessageModel::~MessageModel()
{
  // TODO Auto-generated destructor stub
}

int MessageModel::rowCount(const QModelIndex& parent) const
{
  return messages.size();
}

int MessageModel::columnCount(const QModelIndex& parent) const
{
  // ID, to, from, subject, body
  return 5;
}

QVariant MessageModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
  if (orientation == Qt::Horizontal) {
    switch(section)
      {
        case 0:
          return "Message ID";
        case 1:
          return "To";
        case 2:
          return "From";
        case 3:
          return "Subject";
        case 4:
          return "Body";
        default:
          return "";
      }
  } else {
    return section;
  }
}

QVariant MessageModel::data(const QModelIndex& index, int role) const
{
  const MailMessage& message = messages[index.row()];

  switch(index.column())
    {
      case 0:
        return message.getMessageId();
      case 1:
        return message.getTo();
      case 2:
        return message.getFrom();
      case 3:
        return message.getSubject();
      case 4:
        return message.getBody()[0]; // First line of body
      default:
        return "";
    }
}

void MessageModel::clear()
{
  messages.clear();
}

void MessageModel::addMessage(const MailMessage& message)
{
  messages.push_back(message);
}
