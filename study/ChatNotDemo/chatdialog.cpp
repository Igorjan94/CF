 #include <QtGui>
 #include <cstdio>
 #include <string>
 #include <QUdpSocket>
 #include <ctime>
 #include <QNetworkInterface>

 #include "chatdialog.h"

 using namespace std;

 int getUniqeNick()
 {
     FILE *f;
     f = fopen("nick.txt", "r");
     int i = 0;
     if (f != NULL)
     {
         fscanf(f, "%d", &i);
         fclose(f);
     }
     f = fopen("nick.txt","w+");
     fprintf(f, "%d", ++i);
     fclose(f);
     return i - 1;
 }

 void ChatDialog::getTime(time_t timer, char s[])
 {
     struct tm *t;
     time (&timer);
     t = localtime(&timer);
     sprintf(s, "%d.%d  %d:%d:%d", t->tm_mday, t->tm_mon + 1, t->tm_hour, t->tm_min, t->tm_sec);
 }

 void ChatDialog::logMessage(const QString &nick, const QString &message)
 {
     QByteArray s1 = nick.toUtf8();
     const char *printedString1 = s1.data();
     QByteArray s2 = message.toUtf8();
     const char *printedString2 = s2.data();
     ::printf("#%d %s %s#\n", time(NULL), printedString1, printedString2);
 }

 QUdpSocket *udpSocket = new QUdpSocket(0);

 void ChatDialog::showHistory()
 {
     //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
     freopen("history.tmp", "r", stdin);
     char c;
     string s;
     time_t timer;
     while (true)
     {
         scanf("%c", &c);
         if (c != '#')
             break;
         s = c;
         scanf("%d ", &timer);
         while(true)
         {
             scanf("%c", &c);
             if (c == '#')
                 break;
             s.push_back(c);
         }
         scanf("%c\n", &c);
         s.erase(0, 1);
         QString qstr(s.c_str());
         QTextCursor cursor(textEdit->textCursor());
         cursor.movePosition(QTextCursor::End);
         QColor color = textEdit->textColor();
         if (s[s.size() - 1] == 'd')
            textEdit->setTextColor(Qt::blue); else
            if (s[s.size() - 1] == 't')
                 textEdit->setTextColor(Qt::gray);
         textEdit->append(tr("%1").arg(qstr));
         textEdit->setTextColor(color);
         QScrollBar *bar = textEdit->verticalScrollBar();
         bar->setValue(bar->maximum());
     }
     fclose(stdin);
 }

 QString ChatDialog::localIP(int i)
 {
    QString locIP;
    QList<QHostAddress> addr = QNetworkInterface::allAddresses();
    locIP = addr.at(i).toString();
    return locIP;
 }

 ChatDialog::ChatDialog(QWidget *parent)
     : QDialog(parent)
 {
     setupUi(this);
     udpSocket->bind(3838, QUdpSocket::ShareAddress);
     lineEdit->setFocusPolicy(Qt::StrongFocus);
     textEdit->setFocusPolicy(Qt::NoFocus);
     textEdit->setReadOnly(true);
     listWidget->setFocusPolicy(Qt::NoFocus);
     connect(udpSocket, SIGNAL(readyRead()), this, SLOT(getMsg()));
     int i = getUniqeNick() + '0';
     myNickName = "igorjan";
     myNickName.append(i);
     tableFormat.setBorder(0);
     freopen("history.tmp", "a+", stdout);
     showHistory();
     sendMsg("HELLO", myNickName);
 }

 void ChatDialog::sendMsg(QString nick, QString msg)
 {
    if (msg != "")
    {
       QByteArray datagram;
       datagram.append(nick + ' ' + msg);
       udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, 3838);
       msg = "";
    }
 }

 void ChatDialog::appendMessage(const QString &from, const QString &message)
 {
     if (from.isEmpty() || message.isEmpty())
         return;
     QTextCursor cursor(textEdit->textCursor());
     cursor.movePosition(QTextCursor::End);
     textEdit->append(tr("%1").arg('<' + from + "> " + message));
     QScrollBar *bar = textEdit->verticalScrollBar();
     bar->setValue(bar->maximum());
     logMessage("<" + from + ">", message);
 }

 void ChatDialog::returnPressed()
 {
     QString text = lineEdit->text();
     if (text.isEmpty())
         return;
     sendMsg("MESSAGE" + myNickName, text);
     lineEdit->clear();
 }

 QString ChatDialog::getUserList()
 {
     QString s;
     QList<QListWidgetItem*> items = listWidget->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
     for (int i = 0; i < items.size(); i++)
         s.append(items.at(i)->text()),
         i == items.size() - 1 ? s.append('\n') : s.append(' ');
     return s;
 }

 void ChatDialog::getMsg()
 {
      QByteArray datagram;
      datagram.resize(udpSocket->pendingDatagramSize());
      QHostAddress sender;
      quint16 senderPort;
      udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
      QString text = QString(datagram.data());
      QString nick = "";
      {
      if (text[0] == 'H')
        {
          text.remove(0, 6);
          newParticipant(text);
//          logMessage(myNickName + "oooooo! ", s);
        }
      if (text[0] == 'Q')
        {
          text.remove(0, 5);
          participantLeft(text);
        }
      if (text[0] == 'M')
        {
          text.remove(0, 7);
          int i = 0;
          while (text[i] != ' ')
              nick += text[i],
              i++;
          text.remove(0, i + 1);
          //get time from string
          appendMessage(nick, text);
        }
      }
 }

 void ChatDialog::clearHistory()
 {
     QMessageBox msgBox;
     msgBox.setIcon(QMessageBox::Critical);
     QString str = "Вы уверены, что хотите очистить всю историю сообщений?";
     msgBox.setText(tr("%1").arg(str));
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     if(msgBox.exec() == 16384)
         freopen("history.tmp", "w+", stdout);
 }

 void ChatDialog::printf(QColor color, QString nick, QString did)
 {
     QColor curColor = textEdit->textColor();
     textEdit->setTextColor(color);
     textEdit->append(tr("* %1 has %2").arg(nick, did));
     textEdit->setTextColor(curColor);
     QScrollBar *bar = textEdit->verticalScrollBar();
     bar->setValue(bar->maximum());
     logMessage("* " + nick, "has " + did);
 }

 void ChatDialog::newParticipant(const QString &nick)
 {
     if (nick.isEmpty())
         return;
     printf(Qt::red, nick, "joined");
     listWidget->addItem(nick);
 }

 void ChatDialog::participantLeft(const QString &nick)
 {
     if (nick.isEmpty())
         return;
     QList<QListWidgetItem *> items = listWidget->findItems(nick, Qt::MatchExactly);
     if (items.isEmpty())
         return;
     delete items.at(0);
     printf(Qt::gray, nick, "left");
 }

 ChatDialog::~ChatDialog()
 {
     sendMsg("QUIT", myNickName);
     logMessage("* " + myNickName, "has left");
     //тут должно быть закрытие файла, по хорошему
 }
 /*void Receiver::run() {
    QUdpSocket *udpSocket = new QUdpSocket(0);
    udpSocket->bind(3838, QUdpSocket::ShareAddress);
    while (udpSocket->waitForReadyRead(-1)) {
        if (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            QString text = QString(datagram.data());
            m1.lock();
            label->append(tr("%1").arg(text));
            m1.unlock();
        }
    }
}

void Broadcaster::run() {
    QHostAddress a(QUdpSocket::ShareAddress);
    while (1) {
        m2.lock();
        if (mes != "") {
            QByteArray datagram;
            datagram.append(mes);
            QUdpSocket *udpSocket = new QUdpSocket(0);
            udpSocket->bind(3838, QUdpSocket::ShareAddress);
            udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, 3838);
            mes = "";
        }
        m2.unlock();
    }
}
*/
