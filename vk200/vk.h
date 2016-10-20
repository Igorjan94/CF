#ifndef VK_H
#define VK_H

#include "user.h"
#include "includes.h"
#include "message.h"

#include <QTimer>

namespace Ui {
    class Vk;
}

class Vk : public QWidget
{
    Q_OBJECT

public:
//methods
    explicit Vk(QWidget *parent = 0);
    ~Vk();
//variables

public slots:
    void onReturn();
    void onItemDoubleClicked(QListWidgetItem* item);
    void proceedUnreadDialogs();
    void keyPressEvent(QKeyEvent* event);
    void changeEvent(QEvent* e);

private:
//methods
    void init();
    void addUser(qs s, bool hidden = false);
    void addUser(user u, bool hidden = false);
    bool existsUser(int id);
    void appendTextToCurrentUser(qs text);
    void appendMessage(int user_id, QJsonValue mes);
    void loadHistory(int curr, int count);
    void makeRead(int peer_id);
    void forceUpdate();
    void proceedMessageAttachments(QJsonValue mes);
    qs getStringByAttachment(QJsonValue attachment);
    void sendCommand(QStringList list, std::function<void(QJsonObject x)> callback);
    void send(qs method, std::map<qs, qs> queryParams, std::function<void(QJsonObject x)> callback, std::function<void()> error = [](){});
    void send(qs method, std::map<qs, qs> queryParams, std::function<void(QJsonObject x)> callback, std::function<void(QNetworkReply::NetworkError x)> error);
    //api
        void getHistory(int peer_id, int count, std::function<void(QJsonObject x)> callback);
        void getUserVk(int user_id, std::function<void()> callback = [](){});
        void sendMessage(int peer_id, message m, qs attachment = "");
        void markAsRead(int peer_id);
//variables
    Ui::Vk *ui;
    QFont bold, unbold;
    QTimer* unreadDialogsTimer;

    qs key;
    qs version = "5.53";
    int countOfMessages = 10;
    int offset = 0;
    qs api = "https://api.vk.com/method/";
    std::vector<user> users;
    std::map<qs, int> indices;
    std::map<int, qs> nameById;
    int currentUser = 0;
    volatile bool isRefreshRunning;


    int const CHAT_OFFSET = 2000000000;
    int const AUTO_REFRESH_UNREAD = 10;
};

#endif // VK_H
