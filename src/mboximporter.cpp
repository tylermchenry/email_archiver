/*
 * mboximporter.cpp
 * Part of email_archiver
 *
 *  Created on: Feb 28, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#include "mboximporter.h"
#include <vector>
#include <QTextStream>

MBoxImporter::MBoxImporter()
{
  // TODO Auto-generated constructor stub

}

MBoxImporter::~MBoxImporter()
{
  // TODO Auto-generated destructor stub
}

int MBoxImporter::parse(QFile& mboxFile)
{
  static const QString FROM_FIELD_PREFIX = "From ";
  int messages = 0;

  QTextStream stream(&mboxFile);
  QString line;

  qint64 fileSize = mboxFile.size();
  qint64 bytesRead = 0;
  int pctDone = 0;

  emit progress(pctDone);

  std::vector<QString> currentMessage;

  while (!(line = stream.readLine()).isNull())
  {
    if (line.startsWith(FROM_FIELD_PREFIX)) {

      if (!currentMessage.empty()) {
        ++messages;
        emit newMessage(MailMessage::parseRFC2822(currentMessage));
        currentMessage.clear();
      }

    } else {
      currentMessage.push_back(line);
    }

    bytesRead += line.size();
    int newPctDone = (bytesRead * 100) / fileSize;

    if (newPctDone != pctDone) {
      pctDone = newPctDone;
      emit progress(pctDone);
    }
  }

  return messages;
}
