 #ifndef CHATDIALOG_H
 #define CHATDIALOG_H

 #include "ui_chatdialog.h"
#include "QMessageBox"
#include "QScrollBar"

 class ChatDialog : public QDialog, private Ui::ChatDialog
 {
     Q_OBJECT

 public:
     ChatDialog(QWidget *parent = 0);
     ~ChatDialog();

 public slots:
     void appendMessage(const QString &from, const QString &message);

 private slots:
     void getMsg();
     void returnPressed();
     void newParticipant(const QString &nick);
     void participantLeft(const QString &nick);
     void clearHistory();

 private:
     void sendMsg(QString nick, QString msg);
     void showHistory();
     void printf(QColor color, QString nick, QString did);
     void logMessage(const QString &nick, const QString &message);
     QString myNickName;
     void getTime(time_t timer, char[]);
     QTextTableFormat tableFormat;
     QString localIP(int i);
     QString getUserList();
 };

 #endif
