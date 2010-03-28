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

    inline const std::vector<QString>& getBody() const
    {
        return body;
    }

    inline QString getFrom() const
    {
        return getHeader("From");
    }

    inline QString getMessageId() const
    {
        return getHeader("Message-Id");
    }

    inline QString getHeader(const QString& field) const
    {
      std::multimap<QString, QString>::const_iterator i = headers.find(field.toLower());
      return (i == headers.end()) ? QString() : i->second;
    }

    std::vector<QString> getMultiHeader(const QString& field) const;

    inline const std::multimap<QString, QString>& getHeaders() const
    {
        return headers;
    }

    inline QString getSubject() const
    {
        return getHeader("Subject");
    }

    inline QString getTo() const
    {
        return getHeader("To");
    }

private:

    std::multimap<QString, QString> headers;

    std::vector<QString> body;
};

#endif /* MAILMESSAGE_H_ */
