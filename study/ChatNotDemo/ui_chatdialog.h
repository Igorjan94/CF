/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *History;
    QHBoxLayout *hboxLayout;
    QTextEdit *textEdit;
    QListWidget *listWidget;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QString::fromUtf8("ChatDialog"));
        ChatDialog->resize(704, 529);
        vboxLayout = new QVBoxLayout(ChatDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 8, -1, -1);
        History = new QPushButton(ChatDialog);
        History->setObjectName(QString::fromUtf8("History"));
        History->setMaximumSize(QSize(16777215, 16777215));
        History->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(History);


        vboxLayout->addLayout(horizontalLayout_2);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        textEdit = new QTextEdit(ChatDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMouseTracking(false);
        textEdit->setFocusPolicy(Qt::NoFocus);
        textEdit->setReadOnly(true);

        hboxLayout->addWidget(textEdit);

        listWidget = new QListWidget(ChatDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMaximumSize(QSize(180, 16777215));
        listWidget->setFocusPolicy(Qt::NoFocus);

        hboxLayout->addWidget(listWidget);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label = new QLabel(ChatDialog);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout1->addWidget(label);

        lineEdit = new QLineEdit(ChatDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        hboxLayout1->addWidget(lineEdit);

        pushButton = new QPushButton(ChatDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFocusPolicy(Qt::TabFocus);

        hboxLayout1->addWidget(pushButton);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(ChatDialog);
        QObject::connect(History, SIGNAL(clicked()), ChatDialog, SLOT(clearHistory()));
        QObject::connect(lineEdit, SIGNAL(editingFinished()), ChatDialog, SLOT(returnPressed()));
        QObject::connect(pushButton, SIGNAL(clicked()), ChatDialog, SLOT(returnPressed()));

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QCoreApplication::translate("ChatDialog", "\320\247\320\260\321\202", nullptr));
        History->setText(QCoreApplication::translate("ChatDialog", "\320\276\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\270\321\201\321\202\320\276\321\200\320\270\321\216 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\271", nullptr));
        label->setText(QCoreApplication::translate("ChatDialog", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265:", nullptr));
        pushButton->setText(QCoreApplication::translate("ChatDialog", "\320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
