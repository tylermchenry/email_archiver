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

  QString* prevSpecialHeader;
  std::multimap<QString, QString>::iterator  prevOtherHeader;

  for (std::vector<QString>::const_iterator i = lines.begin();
       i != lines.end(); ++i)

  {
    if (!finishedHeaders) {

      if (i->length() == 0) {
        finishedHeaders = true;
      } else {
        int delimiter_pos = i->indexOf(':');

        if (delimiter_pos == 0) {

          // Continuation of previous header; collapse leading whitespace

          int begin_pos = 0;

          while ((*i)[begin_pos] == ' ' || (*i)[begin_pos] == '\t') ++begin_pos;

          if (prevSpecialHeader) {
            prevSpecialHeader->append(" " + i->right(i->size() - begin_pos));
          } else if (prevOtherHeader != message.otherHeaders.end()) {
            prevOtherHeader->second.append(" " + i->right(i->size() - begin_pos));
          }

        } else {

          // New header

          prevSpecialHeader = NULL;
          prevOtherHeader = message.otherHeaders.end();

          QString field = i->left(delimiter_pos);
          QString value = i->right(i->size() - delimiter_pos - 1);

          if (field.toLower() == "to") {
            message.to = value;
            prevSpecialHeader = &(message.to);
          } else if (field.toLower() == "from") {
            message.from = value;
            prevSpecialHeader = &(message.from);
          } else if (field.toLower() == "subject") {
            message.subject = value;
            prevSpecialHeader = &(message.subject);
          } else if (field.toLower() == "message-id") {
            message.messageId = value;
            prevSpecialHeader = &(message.messageId);
          } else {
            prevOtherHeader = message.otherHeaders.insert
                (std::map<QString, QString>::value_type(field, value));
          }
        }
      }
    }

    if (finishedHeaders) {
      if (!message.body.empty() || i->length() > 0) {
        message.body.push_back(*i);
      }
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


