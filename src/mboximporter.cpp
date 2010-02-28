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

std::size_t MBoxImporter::parse(QFile& mboxFile)
{
  static const QString FROM_FIELD_PREFIX = "From ";

  QTextStream stream(&mboxFile);
  QString line;
  std::vector<MBoxMessage> messages;

  qint64 fileSize = mboxFile.size();
  qint64 bytesRead = 0;
  int pctDone = 0;

  emit progress(pctDone);

  MBoxMessage currentMessage;
  bool finishedHeaders = false;

  while (!(line = stream.readLine()).isNull())
  {
    if (line.startsWith(FROM_FIELD_PREFIX)) {

      if (currentMessage.from != "") {
        messages.push_back(currentMessage);
        currentMessage = MBoxMessage();
        finishedHeaders = false;
      }

      currentMessage.from = line.right(line.size() - FROM_FIELD_PREFIX.size());

    } else if (currentMessage.from != "") {

      if (!finishedHeaders) {

        int delimiter_pos = line.indexOf(':');

        if (delimiter_pos == 0) {
          finishedHeaders = true;
        } else {
          currentMessage.headers.insert(std::map<QString, QString>::value_type
                                        (line.left(delimiter_pos),
                                         line.right(line.size() - delimiter_pos - 1)));
        }
      }

      if (finishedHeaders) {
        currentMessage.body += line + '\n';
      }
    }

    bytesRead += line.size();
    int newPctDone = (bytesRead * 100) / fileSize;

    if (newPctDone != pctDone) {
      pctDone = newPctDone;
      emit progress(pctDone);
    }
  }

  return messages.size();
}
