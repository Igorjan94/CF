#ifndef MESSAGE_H
#define MESSAGE_H

#include "includes.h"

struct message
{
    qs text;
    qs author;
    QDateTime date;
    int id;

    message() {}

    message(qs text, int date = -1, qs author = "Я")
    {
        this->text = text;
        this->date.setTime_t(date == -1 ? QDateTime::currentMSecsSinceEpoch() / 1000 : (date - 3 * 60 * 60));
        this->author = author;
    }

    operator qs()
    {
        return date.toString(Qt::SystemLocaleShortDate) + ": " + author + (text == "" ? "" : "\n" TAB + text);
    }
};

#endif // MESSAGE_H
