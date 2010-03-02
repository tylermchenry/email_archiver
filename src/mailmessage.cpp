/*
 * mailmessage.cpp
 * Part of email_archiver
 *
 *  Created on: Mar 1, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#include "mailmessage.h"
#include <QTextStream>

MailMessage MailMessage::parseRFC2822(const std::vector<QString>& lines)
{
  MailMessage message;
  bool finishedHeaders = false;

  for (std::vector<QString>::const_iterator i = lines.begin();
       i != lines.end(); ++i)

  {
    if (!finishedHeaders) {

      int delimiter_pos = i->indexOf(':');

      if (delimiter_pos == 0) {
        finishedHeaders = true;
      } else {
        QString field = i->left(delimiter_pos);
        QString value = i->right(i->size() - delimiter_pos - 1);

        if (field.toLower() == "to") {
          message.to = value;
        } else if (field.toLower() == "from") {
          message.from = value;
        } else if (field.toLower() == "subject") {
          message.subject = value;
        } else if (field.toLower() == "message-id") {
          message.messageId = value;
        } else {
          message.otherHeaders.insert
            (std::map<QString, QString>::value_type(field, value));
        }
      }
    }

    if (finishedHeaders) {
      message.body.push_back(*i);
    }
  }

  return message;
}

MailMessage MailMessage::parseRFC2822(QString message)
{
  QTextStream stream(&message);
  std::vector<QString> lines;
  QString line;

  while (!(line = stream.readLine()).isNull())
  {
    lines.push_back(line);
  }

  return parseRFC2822(lines);
}


MailMessage::MailMessage()
{
}

MailMessage::~MailMessage()
{
}


