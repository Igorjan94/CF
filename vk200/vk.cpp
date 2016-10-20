#include "vk.h"
#include "ui_vk.h"

#include "includes.h"
#include "debug.h"

QJsonValue getValue(QJsonValue value, qs what) { for (qs s : what.split('.')) value = value.toObject()[s]; return value; }
QJsonArray getArray(QJsonValue value, qs what) { return getValue(value, what).toArray(); }
QString getString(QJsonValue value, qs what) { return getValue(value, what).toString(); }
int getInt(QJsonValue value, qs what) { return getValue(value, what).toInt(); }

template<typename T>
qs toString(T value)
{
    QJsonDocument doc(value);
    return doc.toJson(QJsonDocument::Indented);
}

auto readFile(qs filename, bool failOnError = false)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        if (failOnError)
            error("File \"" + filename + "\" is not found");
        else
            return vector<qs>();
    }
    QTextStream in(&file);
    vector<qs> strings;

    while (!in.atEnd())
        strings.push_back(in.readLine());
    file.close();
    return strings;
}

user getUser(qs& s)
{
    auto parsed = s.split(' ');
    int id = parsed[0].toLongLong();
    parsed.erase(parsed.begin());
    qs username = parsed.join(' ');
    return user(id, username);
}

void Vk::appendTextToCurrentUser(qs text)
{
    if (currentUser == -1)
        return;
    users[currentUser].text += text + "\n";
    ui->textBrowser->setHtml(users[currentUser].text.replace('\n', "<br>"));
    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
}

void Vk::getHistory(int peer_id, int count, std::function<void(QJsonObject x)> callback)
{
    map<qs, qs> params;
    params["peer_id"] = qs::number(peer_id);
    params["count"] = qs::number(count);
    if (offset)
        params["offset"] = qs::number(offset);
    send("messages.getHistory", params, callback);
}

void Vk::getUserVk(int user_id, std::function<void()> callback)
{
    if (existsUser(user_id))
    {
        callback();
        return;
    }
    writeln("Пользователь", user_id, "не существует, получаем из ВК");
    map<qs, qs> params;
    bool isUser = user_id < CHAT_OFFSET;
    params[isUser ? "user_ids" : "chat_ids"] = qs::number(user_id - (!isUser) * CHAT_OFFSET);
    send(isUser ? "users.get" : "messages.getChat", params, [&](QJsonObject x) {
        //Если ВК ответил, добавим нового пользователя и добавим сообщение
        auto userDetails = getArray(x, "response")[0];
        addUser(user(user_id, isUser ? (getString(userDetails, "first_name") + " " + getString(userDetails, "last_name")) : getString(userDetails, "title")));
        callback();
    }, callback);
}

void Vk::markAsRead(int peer_id)
{
    map<qs, qs> params;
    params["peer_id"] = qs::number(peer_id);
    send("messages.markAsRead", params, [&](QJsonObject x) {
        writeln("Пользователь", peer_id, "помечен прочитанным", getInt(x, "response"));
        makeRead(peer_id);
    }, [&]() {
        writeln("Не удалось пометить пользователя", peer_id, "прочитанным");
    });
}

void Vk::makeRead(int peer_id)
{
    int curr = indices[nameById[peer_id]];
    users[curr].shown = users[curr].unread = 0;
    ui->listWidget->item(curr)->setText(users[curr].name);
    ui->listWidget->item(curr)->setFont(unbold);
}

void Vk::sendMessage(int peer_id, message m, qs attachment)
{
    map<qs, qs> params;
    params["peer_id"] = qs::number(peer_id);
    params["message"] = m.text;
    if (attachment != "")
        params["attachment"] = attachment;
    proceedUnreadDialogs();
    send("messages.send", params, [&](QJsonObject x) {
        writeln("Сообщение \"", m.text, "\" успешно отправлено", peer_id, getInt(x, "response"));
        makeRead(peer_id);
    }, [&]() {
        appendTextToCurrentUser("-------- Не удалось отправить сообщение \"" + m.text + "\" пользователю " + qs::number(peer_id) + " --------");
    });
}

void Vk::sendCommand(QStringList list, std::function<void(QJsonObject x)> callback)
{
    map<qs, qs> params;
    for (int i = 1; i + 1 < list.size(); i += 2)
        params[list[i]] = list[i + 1];
    send(list[0], params, [&](QJsonObject x) {
        writeln("Команда успешно выполнена");
        callback(x);
    }, [&]() {
        writeln("Не удалось выполнить команду");
    });
}

void Vk::proceedUnreadDialogs()
{
    if (isRefreshRunning)
        return;
    isRefreshRunning = true;
    map<qs, qs> params;
    params["unread"] = "1";
    params["count"] = qs::number(countOfMessages);
    send("messages.getDialogs", params, [&](QJsonObject x) {
        if (getInt(x, "response.count"))
            for (auto temp : getArray(x, "response.items"))
            {
                auto mes = getValue(temp, "message");

                int peer_id = getInt(mes, "user_id");
                if (!getValue(mes, "chat_id").isNull())
                {
                    peer_id = CHAT_OFFSET + getInt(mes, "chat_id");
                    addUser(user(peer_id, getString(mes, "title")));
                }
                getUserVk(peer_id, [&]() {
                    int curr = indices[nameById[peer_id]];
                    users[curr].unread = getInt(temp, "unread");

                    ui->listWidget->item(curr)->setFont(bold);
                    ui->listWidget->item(curr)->setText(users[curr].name + " (" + qs::number(users[curr].unread) + ")");

                    if (curr == currentUser)
                        loadHistory(curr, -1);
                });
            }
        isRefreshRunning = false;
    }, [&]() {
        isRefreshRunning = false;
        writeln("Что-то пошло не так, не получается загрузить непрочитанные сообщения");
    });
}

qs getLink(qs link, qs text = "Картинка")
{
    return "<a href=\"" + link + "\">" + text + "</a>";
}

qs Vk::getStringByAttachment(QJsonValue attachment)
{
    qs type = getString(attachment, "type");
    if (type == "photo")
    {
        auto photo = getValue(attachment, "photo").toObject();
        int mx = 0;
        for (auto key : photo.keys())
            if (key.startsWith("photo"))
                mx = max(mx, key.split("_")[1].toInt());
        return TAB + getLink(getString(photo, "photo_" + qs::number(mx)));
    } 
    else
    if (type == "link")
    {
        auto link = getValue(attachment, "link").toObject();
        return TAB"Ссылка: " + getLink(getString(link, "url"), getString(link, "title")) + " (" + getString(link, "description") + ")";
    }
    else
    if (type == "wall")
    {
        auto wall = getValue(attachment, "wall").toObject();
        proceedMessageAttachments(wall);
        return TAB + getString(wall, "text");
    }
    else
    if (type == "doc")
    {
        auto doc = getValue(attachment, "doc").toObject();
        return TAB + getLink(getString(doc, "url"), getString(doc, "title"));
    }
    else
        writeln("Неизвестный мне аттач(или мне лень)", toString(attachment.toObject()));
    return type;
}

void Vk::proceedMessageAttachments(QJsonValue mes)
{
    auto attachments = getValue(mes, "attachments");
    if (!attachments.isNull())
        for (auto attachment : attachments.toArray())
            appendTextToCurrentUser(getStringByAttachment(attachment));
    auto fwd = getValue(mes, "fwd_messages");
    if (!fwd.isNull())
    {
        appendTextToCurrentUser("---Переадресованные сообщения---");
        for (auto m : fwd.toArray())
            appendMessage(users[currentUser].id, m);
        appendTextToCurrentUser("---Переадресованные сообщения конец---");
    }
}

void Vk::appendMessage(int user_id, QJsonValue mes)
{
    getUserVk(user_id);
    int author_id = getInt(mes, "from_id");
    //API unread возвращает user chat, вместо peer и from
    if (getValue(mes, "from_id").isNull())
        author_id = getInt(mes, "user_id");

    auto proceedMessage = [&]() {
        //Создадим сообщение
        message m(getString(mes, "action") + getString(mes, "body"), getInt(mes, "date") + 3 * 60 * 60, nameById[author_id]);
        writeln("Получено сообщение", m.text);
        //Если все еще смотрим на этого юзера -- вставим текст
        if (currentUser != -1 && user_id == users[currentUser].id)
        {
            appendTextToCurrentUser(m);
            proceedMessageAttachments(mes);
        }
    };

    //Загрузим пользователя, если он не существует
    if (existsUser(author_id))
        proceedMessage();
    else
        getUserVk(author_id, proceedMessage);
}

void Vk::loadHistory(int curr, int count = -1)
{
    auto user_id = users[curr].id;
    if (count == -1)
        count = users[curr].isInitialized ? users[curr].unread - users[curr].shown : (countOfMessages + users[curr].unread);
    writeln("Получаю", count, "сообщений от пользователя", user_id);
    if (count)
        getHistory(user_id, count, [&](QJsonObject x) {
            auto messages = getArray(x, "response.items");
            //В обратном порядке
            for (int i = int(messages.size()) - 1; i >= 0; --i)
            {
                appendMessage(user_id, messages[i]);
                //auto lichinka = 2000000021;
                //if (user_id == lichinka && getInt(messages[i], "from_id") == 575332 && users[curr].isInitialized)
                    //sendMessage(lichinka, message("💩"));
            }
            users[curr].shown = users[curr].unread;
            users[curr].isInitialized = true;
        });
}

void Vk::onItemDoubleClicked(QListWidgetItem* item)
{
    //Снимаем выделение
    item->setFont(unbold);
    int index = indices[item->text().split(" (")[0]];
    //Сохраним текущий текст непосредственно в пользователя
    if (currentUser != -1)
        users[currentUser].currentText = ui->lineEdit->text();
    //Если это текущий пользователь, дальше ничего не делаем
    if (index == currentUser)
        return;

    //Получаем нового пользователя
    user u = users[currentUser = index];
    writeln("Выбран пользователь: " + u);
    //Ставим заголовок
    this->setWindowTitle(u.name);
    //Ставим сохраненный текст
    ui->lineEdit->setText(u.currentText);
    ui->textBrowser->setHtml(u.text);
    ui->textBrowser->verticalScrollBar()->setValue(ui->textBrowser->verticalScrollBar()->maximum());
    loadHistory(currentUser);
}

void Vk::send(qs method, map<qs, qs> queryParams, std::function<void(QJsonObject x)> callback, std::function<void()> error)
{
    send(method, queryParams, callback, [&](QNetworkReply::NetworkError x) {
        writeln("При работе с сетью случилась ошибка:", x);
        error();
    });
}

void Vk::send(qs method, map<qs, qs> queryParams, std::function<void(QJsonObject x)> callback, std::function<void(QNetworkReply::NetworkError x)> error)
{
    QUrl params;
    QUrlQuery query;
    //ПАЩИМУ??? Я ТЕБЯ СПРАШИВАЮ ПЕРВЫЙ ПАРАМЕТР НЕ РАБОТАЕТ ИЛИ НЕТ?
    query.addQueryItem("v", version);
    query.addQueryItem("v", version);
    query.addQueryItem("access_token", key);

    for (auto param : queryParams)
        query.addQueryItem(param.first, param.second);
    params.setQuery(query);

    QNetworkRequest networkRequest(QUrl(api + method));
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkAccessManager netAccessMan;
    QNetworkReply *reply = netAccessMan.post(networkRequest, params.toEncoded(QUrl::RemoveFragment));
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, [&] () {
        auto response = QJsonDocument::fromJson(reply->readAll()).object();
        if (!getValue(response, "error").isNull())
        {
            writeln("Запрос некорректен:", toString(getValue(response, "error").toObject()));
            error(QNetworkReply::NoError);
        }
        else
            callback(response);
        reply->deleteLater();
        loop.quit();
    });
    //Какая-то магия. Зато работает
    QObject::connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), error);
    loop.exec();
}

void Vk::forceUpdate()
{
    if (currentUser == -1)
        return;
    writeln("Насильная загрузка истории", users[currentUser].id);
    users[currentUser].text = "";
    loadHistory(currentUser, countOfMessages);
}

void Vk::onReturn()
{
    qs text = ui->lineEdit->text();
    ui->lineEdit->clear();
    if (text == "")
        return;
    if (text[0] == '/' && text.size() > 1)
    {
        auto spl = text.remove(0, 1).split(" ");
        auto command = spl[0];
        if ((command == "c" || command == "count") && spl.size() >= 2)
        {
            countOfMessages = spl[1].toInt();
            writeln("Количество загружаемых сообщений", countOfMessages);
            forceUpdate();
        }
        if (command == "m" && currentUser != -1)
            markAsRead(users[currentUser].id);
        if ((command == "u" || command == "user") && spl.size() >= 2)
            getUserVk(spl[1].toInt(), [&]() {
                writeln("Добавлен пользователь", spl[1]);
            });
        if ((command == "d" || command == "chat") && spl.size() >= 2)
            getUserVk(spl[1].toInt() + CHAT_OFFSET, [&]() {
                writeln("Добавлен чат", spl[1]);
            });
        if ((command == "e" || command == "execute") && spl.size() >= 2)
        {
            writeln("Выполняю команду:", "/" + text);
            spl.removeAt(0);
            sendCommand(spl, [&](QJsonObject x) {
                writeln(toString(x));
            });
        }
        if ((command == "f" || command == "friends"))
        {
            writeln("Запрашиваю запросы на добавление в друзья");
            sendCommand({"friends.getRequests"}, [](QJsonObject x) {
                if (getInt(x, "response.count") == 0)
                    writeln("Нет запросов на добавление в друзья");
                for (auto id : getArray(x, "response.items"))
                    writeln("https://vk.com/id" + qs::number(id.toInt()), id.toInt());
            });
        }
        if (command == "add" && spl.size() >= 2)
        {
            int user_id = spl[1].toInt();
            writeln("Подтверждаю запрос на добавление в друзья", user_id);
            sendCommand({"friends.add", "user_id", spl[1]}, [&](QJsonObject x) {
                writeln("Запрос пользователя", user_id, "подтвержден", toString(x));
            });
        }
        if (command == "delete" && spl.size() >= 2)
        {
            int user_id = spl[1].toInt();
            writeln("Удаляю запрос на добавление в друзья", user_id);
            sendCommand({"friends.delete", "user_id", spl[1]}, [&](QJsonObject x) {
                writeln("Запрос пользователя", user_id, "удален", toString(x));
            });
        }
        if ((command == "offset" || command == "o") && spl.size() >= 2)
        {
            offset = spl[1].toInt();
            writeln("Ставлю сдвиг сообщений в прошлое", offset);
        }
        if (command == "?" || command == "help")
        {
            writeln("c[ount] <countOfMessages>");
            writeln("m");
            writeln("u[ser] <user_id>");
            writeln("d[chat] <chat_id>");
            writeln("e[xecute] <method> <param value>...");
            writeln("f[riends]");
            writeln("o[ffset] <offset>"); 
            writeln("?[help]");
        }
        if (command == "посрать")
            sendMessage(users[currentUser].id, message("💩"));
        if (command == "attach" && spl.size() >= 2)
            sendMessage(users[currentUser].id, message(""), spl[1]);
    }
    else
    {
        if (currentUser == -1)
            return;
        message m(text.replace("\\n", "\n").replace("\\т", "\n"));
        users[currentUser].currentText = "";
        ui->lineEdit->clear();
        appendTextToCurrentUser(m);
        sendMessage(users[currentUser].id, m);
    }
}

void Vk::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
        return;
    if ((event->modifiers() & Qt::ShiftModifier) && (event->key() == Qt::Key_F5))
    {
        forceUpdate();
        return;
    }
    if(((event->modifiers() & Qt::ControlModifier) && (event->key() == Qt::Key_R)) || event->key() == Qt::Key_F5)
    {
        writeln("Насильное обновление");
        proceedUnreadDialogs();
        return;
    }
    if(event->modifiers() & Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_M && currentUser != -1)
            markAsRead(users[currentUser].id);
        if (event->key() == Qt::Key_L)
            return;
        if (event->key() == Qt::Key_N)
        {
            writeln("Счетчики:");
            sendCommand({"account.getCounters"}, [&](QJsonObject x) {
                writeln(toString(x));
            });
        }
    }
    QWidget::keyPressEvent(event);
}

void Vk::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::ActivationChange)
    {
        if (this->isActiveWindow())
        {
            writeln("Данное окно активированно");
            proceedUnreadDialogs();
            unreadDialogsTimer->start();
        }
        if (!this->isActiveWindow())
        {
            writeln("Ухожу в фон");
            unreadDialogsTimer->stop();
        }
    }
    QWidget::changeEvent(e);
}

bool Vk::existsUser(int id)
{
    return nameById.find(id) != nameById.end();
}

void Vk::addUser(user u, bool hidden)
{
    if (existsUser(u.id))
    {
        ui->listWidget->item(indices[u.name])->setHidden(false);
        return;
    }

    ui->listWidget->addItem(u.name);
    indices[u.name] = users.size();
    nameById[u.id] = u.name;
    if (hidden)
        ui->listWidget->item(users.size())->setHidden(true);

    users.push_back(u);
}

void Vk::addUser(qs s, bool hidden)
{
    addUser(getUser(s), hidden);
}

void Vk::init()
{
    key = readFile("key.vk", true)[0];
    for (qs s : readFile("database"))
        addUser(s);
    for (qs s : readFile("fullDatabase"))
        addUser(s, true);
    nameById[3586834] = "Я";

    qs mySecondName = "Игорь Колобов";
    if (indices.find(mySecondName) == indices.end())
        currentUser = -1;
    else
    {
        currentUser = indices[mySecondName];
        ui->listWidget->item(currentUser)->setSelected(true);
        loadHistory(currentUser);
    }   

    unreadDialogsTimer = new QTimer(this);
    connect(unreadDialogsTimer, SIGNAL(timeout()), this, SLOT(proceedUnreadDialogs()));
    unreadDialogsTimer->start(AUTO_REFRESH_UNREAD * 1000);
    proceedUnreadDialogs();
    ui->textBrowser->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

Vk::Vk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vk)
{
    ui->setupUi(this);
    ui->textBrowser->setOpenExternalLinks(true);
    ui->textBrowser->copyAvailable(true);
    ui->textBrowser->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
    this->setWindowIcon(QIcon("vk.png"));
    bold.setBold(true);
    unbold.setBold(false);

    init();
}

Vk::~Vk()
{
    delete ui;
    delete unreadDialogsTimer;
}
