/*
 * messagedetailsmodel.cpp
 * Part of email_archiver
 *
 *  Created on: Mar 28, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#include "messagedetailsmodel.h"

MessageDetailsModel::MessageDetailsModel(QObject* parent)
  : QAbstractTableModel(parent)
{
  // TODO Auto-generated constructor stub

}

MessageDetailsModel::~MessageDetailsModel()
{
  // TODO Auto-generated destructor stub
}


int MessageDetailsModel::rowCount(const QModelIndex& parent) const
{
  return message.getHeaders().size() + message.getBody().size();
}

int MessageDetailsModel::columnCount(const QModelIndex& parent) const
{
  // field, value
  return 2;
}

QVariant MessageDetailsModel::headerData(int section, Qt::Orientation orientation,
                                      int role) const
{
  if (role == Qt::DisplayRole) {
    if (orientation == Qt::Horizontal) {
      switch(section)
      {
        case 0:
          return "Field";
        case 1:
          return "Value";
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

QVariant MessageDetailsModel::data(const QModelIndex& index, int role) const
{
  if (role == Qt::DisplayRole) {

    if (index.row() < message.getHeaders().size()) {

      // TODO: More efficient
      std::multimap<QString, QString>::const_iterator i = message.getHeaders().begin();
      std::advance(i, index.row());

      switch(index.column())
      {
        case 0:
          return i->first;
        case 1:
          return i->second;
        default:
          return "";
      }
    } else if (index.row() - message.getHeaders().size() < message.getBody().size()) {
      int bodyLine = index.row() - message.getHeaders().size();
      switch(index.column())
      {
         case 0:
           return (bodyLine == 0) ? "Body" : "";
         case 1:
           return message.getBody()[bodyLine];
         default:
           return "";
      }
    } else {
      return "";
    }
  }

  return QVariant();
}

void MessageDetailsModel::clear()
{
  beginRemoveRows(QModelIndex(), message.getHeaders().size() + message.getBody().size(),
                  message.getHeaders().size() + message.getBody().size());
  message = MailMessage();
  endRemoveRows();
  reset();
}

void MessageDetailsModel::setMessage(const MailMessage& message)
{
  clear();
  beginInsertRows(QModelIndex(), 0,
                  message.getHeaders().size() + message.getBody().size());
  this->message = message;
  endInsertRows();
  reset();
}
