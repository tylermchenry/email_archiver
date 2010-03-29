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

  std::multimap<QString, QString>::iterator prevHeader = message.headers.end();

  for (std::vector<QString>::const_iterator i = lines.begin();
       i != lines.end(); ++i)

  {
    if (!finishedHeaders) {

      if (i->length() == 0) {
        finishedHeaders = true;
      } else {

        if ((*i)[0] == ' ' || (*i)[0] == '\t') {

          // Continuation of previous header; collapse leading whitespace

          int begin_pos = 0;

          // QString doesn't have an equivalent to find_first_not_of?
          while (begin_pos < i->length() &&
                 ((*i)[begin_pos] == ' ' || (*i)[begin_pos] == '\t'))
          {
            ++begin_pos;
          }

          if (begin_pos < i->length()) {
            if (prevHeader != message.headers.end()) {
              prevHeader->second.append(" " + i->right(i->size() - begin_pos));
            }
          }

        } else {

          int delimiter_pos = i->indexOf(':');

          // New header

          QString field = i->left(delimiter_pos).toLower();
          QString value = i->right(i->size() - delimiter_pos - 1);

          prevHeader = message.headers.insert
               (std::map<QString, QString>::value_type(field, value));
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

std::vector<QString> MailMessage::getMultiHeader(const QString& field) const
{
  std::vector<QString> mHeader;

  std::pair<std::multimap<QString,QString>::const_iterator,
            std::multimap<QString,QString>::const_iterator> range =
                headers.equal_range(field.toLower());

  for(std::multimap<QString,QString>::const_iterator i = range.first;
      i != range.second; ++i)
  {
    mHeader.push_back(i->second);
  }

  return mHeader;
}

