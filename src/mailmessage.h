/*
 * mailmessage.h
 * Part of email_archiver
 *
 *  Created on: Mar 1, 2010
 *      Author: Tyler McHenry <tyler@nerdland.net>
 */

#ifndef MAILMESSAGE_H_
#define MAILMESSAGE_H_

#include <QString>
#include <vector>
#include <map>

class MailMessage
{
  public:

    static MailMessage parseRFC2822(const std::vector<QString>& lines);

    static MailMessage parseRFC2822(QString message);

    MailMessage();

    virtual ~MailMessage();

    inline std::vector<QString> getBody() const
    {
        return body;
    }

    inline QString getFrom() const
    {
        return from;
    }

    inline QString getMessageId() const
    {
        return messageId;
    }

    inline std::multimap<QString, QString> getOtherHeaders() const
    {
        return otherHeaders;
    }

    inline QString getSubject() const
    {
        return subject;
    }

    inline QString getTo() const
    {
        return to;
    }

private:

    QString messageId;
    QString from;
    QString to;
    QString subject;

    std::multimap<QString, QString> otherHeaders;

    std::vector<QString> body;
};

#endif /* MAILMESSAGE_H_ */
