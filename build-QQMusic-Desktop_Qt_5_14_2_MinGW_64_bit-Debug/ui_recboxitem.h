/********************************************************************************
** Form generated from reading UI file 'recboxitem.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECBOXITEM_H
#define UI_RECBOXITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecBoxItem
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *musicImageBox;
    QLabel *recMusicImage;
    QPushButton *recMusicBtn;
    QLabel *recBoxItemText;

    void setupUi(QWidget *RecBoxItem)
    {
        if (RecBoxItem->objectName().isEmpty())
            RecBoxItem->setObjectName(QString::fromUtf8("RecBoxItem"));
        RecBoxItem->resize(150, 200);
        verticalLayout = new QVBoxLayout(RecBoxItem);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        musicImageBox = new QWidget(RecBoxItem);
        musicImageBox->setObjectName(QString::fromUtf8("musicImageBox"));
        musicImageBox->setMinimumSize(QSize(0, 150));
        musicImageBox->setMaximumSize(QSize(16777215, 150));
        recMusicImage = new QLabel(musicImageBox);
        recMusicImage->setObjectName(QString::fromUtf8("recMusicImage"));
        recMusicImage->setGeometry(QRect(0, 0, 150, 150));
        recMusicImage->setStyleSheet(QString::fromUtf8("background-color:rgb(85, 255, 255);"));
        recMusicBtn = new QPushButton(musicImageBox);
        recMusicBtn->setObjectName(QString::fromUtf8("recMusicBtn"));
        recMusicBtn->setGeometry(QRect(20, 60, 99, 28));
        recMusicBtn->setStyleSheet(QString::fromUtf8("#recMusicBtn\n"
"{\n"
"	background-color:rgb(85, 255, 0);\n"
"	border:none;\n"
"}"));

        verticalLayout->addWidget(musicImageBox);

        recBoxItemText = new QLabel(RecBoxItem);
        recBoxItemText->setObjectName(QString::fromUtf8("recBoxItemText"));
        recBoxItemText->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(recBoxItemText);


        retranslateUi(RecBoxItem);

        QMetaObject::connectSlotsByName(RecBoxItem);
    } // setupUi

    void retranslateUi(QWidget *RecBoxItem)
    {
        RecBoxItem->setWindowTitle(QCoreApplication::translate("RecBoxItem", "Form", nullptr));
        recMusicImage->setText(QString());
        recMusicBtn->setText(QString());
        recBoxItemText->setText(QCoreApplication::translate("RecBoxItem", "\346\216\250\350\215\220-001", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecBoxItem: public Ui_RecBoxItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECBOXITEM_H
