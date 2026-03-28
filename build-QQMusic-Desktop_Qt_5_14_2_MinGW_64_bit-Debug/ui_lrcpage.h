/********************************************************************************
** Form generated from reading UI file 'lrcpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LRCPAGE_H
#define UI_LRCPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LrcPage
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *btStyle;
    QVBoxLayout *verticalLayout;
    QWidget *lrcTop;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *hideBtn;
    QWidget *titltBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *musicSinger;
    QLabel *musicName;
    QWidget *lrcContent;
    QLabel *label;

    void setupUi(QWidget *LrcPage)
    {
        if (LrcPage->objectName().isEmpty())
            LrcPage->setObjectName(QString::fromUtf8("LrcPage"));
        LrcPage->resize(1020, 680);
        horizontalLayout = new QHBoxLayout(LrcPage);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btStyle = new QWidget(LrcPage);
        btStyle->setObjectName(QString::fromUtf8("btStyle"));
        verticalLayout = new QVBoxLayout(btStyle);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lrcTop = new QWidget(btStyle);
        lrcTop->setObjectName(QString::fromUtf8("lrcTop"));
        lrcTop->setMinimumSize(QSize(0, 50));
        lrcTop->setMaximumSize(QSize(16777215, 50));
        lrcTop->setStyleSheet(QString::fromUtf8("background-color:rgb(170, 170, 255);"));
        horizontalLayout_2 = new QHBoxLayout(lrcTop);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 0, 0);
        hideBtn = new QPushButton(lrcTop);
        hideBtn->setObjectName(QString::fromUtf8("hideBtn"));
        hideBtn->setMinimumSize(QSize(30, 50));
        hideBtn->setMaximumSize(QSize(30, 50));

        horizontalLayout_2->addWidget(hideBtn);

        titltBox = new QWidget(lrcTop);
        titltBox->setObjectName(QString::fromUtf8("titltBox"));
        titltBox->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 170, 127);"));
        verticalLayout_2 = new QVBoxLayout(titltBox);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        musicSinger = new QLabel(titltBox);
        musicSinger->setObjectName(QString::fromUtf8("musicSinger"));
        musicSinger->setStyleSheet(QString::fromUtf8("background-color:rgb(170, 170, 0);"));
        musicSinger->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(musicSinger);

        musicName = new QLabel(titltBox);
        musicName->setObjectName(QString::fromUtf8("musicName"));
        musicName->setStyleSheet(QString::fromUtf8("background-color:rgb(170, 170, 255);"));
        musicName->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(musicName);


        horizontalLayout_2->addWidget(titltBox);


        verticalLayout->addWidget(lrcTop);

        lrcContent = new QWidget(btStyle);
        lrcContent->setObjectName(QString::fromUtf8("lrcContent"));
        lrcContent->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 127);"));
        label = new QLabel(lrcContent);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(440, 30, 281, 16));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lrcContent);


        horizontalLayout->addWidget(btStyle);


        retranslateUi(LrcPage);

        QMetaObject::connectSlotsByName(LrcPage);
    } // setupUi

    void retranslateUi(QWidget *LrcPage)
    {
        LrcPage->setWindowTitle(QCoreApplication::translate("LrcPage", "Form", nullptr));
        hideBtn->setText(QString());
        musicSinger->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        musicName->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LrcPage: public Ui_LrcPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LRCPAGE_H
