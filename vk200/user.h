#ifndef USER_H
#define USER_H

#include "includes.h"
#include "message.h"

struct user
{
    qs name;
    qs text;
    qs currentText;
    bool isInitialized = false;
    int unread = 0;
    int shown = 0;
    int id;

    std::vector<message> messages;

    user() {}

    user(int id, qs name)
    {
        this->id = id;
        this->name = name;
    }

    operator qs()
    {
        return name + " (" + qs::number(id) + ")";
    }
};

#endif // USER_H
