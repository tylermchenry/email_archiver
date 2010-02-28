/*
 * mboximporter.h
 * Part of email_archiver
 *
 *  Created on: Feb 28, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#ifndef MBOXIMPORTER_H_
#define MBOXIMPORTER_H_

#include <QString>
#include <QFile>
#include <map>

class MBoxImporter
{
  public:

    // Temporary
    struct MBoxMessage {
      QString from;
      std::map<QString, QString> headers;
      QString body;
    };

    MBoxImporter();
    virtual ~MBoxImporter();

    std::size_t parse(QFile& mboxFile);
};

#endif /* MBOXIMPORTER_H_ */
