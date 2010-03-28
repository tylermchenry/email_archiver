/*
 * messagemodel.cpp
 * Part of email_archiver
 *
 *  Created on: Mar 1, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#include "messagemodel.h"
#include <set>

MessageModel::MessageModel(QObject* parent)
  : QAbstractTableModel(parent)
{

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
  if (role == Qt::DisplayRole) {
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
  } else {
    return QVariant();
  }
}

QVariant MessageModel::data(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole) {
    if (index.row() < messages.size()) {
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
          if (message.getBody().size() > 0) {
            return message.getBody()[0]; // First line of body
          } else {
            return "";
          }
      }
    }
  }

  return QVariant();
}

void MessageModel::clear()
{
  beginRemoveRows(QModelIndex(), messages.size(), messages.size());
  messages.clear();
  endRemoveRows();
  reset();
}

void MessageModel::addMessage(const MailMessage& message)
{
  beginInsertRows(QModelIndex(), messages.size(), messages.size());
  messages.push_back(message);
  endInsertRows();
}

void MessageModel::selectMessage(const QModelIndex& selected,
                                      const QModelIndex& deselected)
{
  if (deselected.row() > 0 && deselected.row() < messages.size()) {
    emit messageDeselected(messages[deselected.row()]);
  }

  if (selected.row() > 0 && selected.row() < messages.size()) {
    emit messageSelected(messages[selected.row()]);
  }
}
