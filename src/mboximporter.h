/*
 * mboximporter.h
 * Part of email_archiver
 *
 *  Created on: Feb 28, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#ifndef MBOXIMPORTER_H_
#define MBOXIMPORTER_H_

#include "mailmessage.h"
#include <QObject>
#include <QString>
#include <QFile>

class MBoxImporter : public QObject
{
    Q_OBJECT

  public:

    MBoxImporter();
    virtual ~MBoxImporter();

    int parse(QFile& mboxFile);

  signals:

    void progress(int percentDone);
    void newMessage(const MailMessage& message);

};

#endif /* MBOXIMPORTER_H_ */
