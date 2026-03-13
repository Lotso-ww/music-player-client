/********************************************************************************
** Form generated from reading UI file 'commonpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONPAGE_H
#define UI_COMMONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommonPage
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *PageTittle;
    QWidget *musicPlayBox;
    QHBoxLayout *horizontalLayout;
    QLabel *musicImageLabel;
    QWidget *playAll;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *playAllBtn;
    QSpacerItem *horizontalSpacer;
    QWidget *listLabelBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *musicNameLabel;
    QLabel *musicSingerLabel;
    QLabel *musicAlbumLabel;
    QListWidget *pageMusicList;

    void setupUi(QWidget *CommonPage)
    {
        if (CommonPage->objectName().isEmpty())
            CommonPage->setObjectName(QString::fromUtf8("CommonPage"));
        CommonPage->resize(800, 500);
        verticalLayout = new QVBoxLayout(CommonPage);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 0, 3, 0);
        PageTittle = new QLabel(CommonPage);
        PageTittle->setObjectName(QString::fromUtf8("PageTittle"));
        PageTittle->setMinimumSize(QSize(0, 30));
        PageTittle->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(PageTittle);

        musicPlayBox = new QWidget(CommonPage);
        musicPlayBox->setObjectName(QString::fromUtf8("musicPlayBox"));
        musicPlayBox->setMinimumSize(QSize(0, 150));
        musicPlayBox->setMaximumSize(QSize(16777215, 150));
        musicPlayBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(musicPlayBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(4, 0, 0, 0);
        musicImageLabel = new QLabel(musicPlayBox);
        musicImageLabel->setObjectName(QString::fromUtf8("musicImageLabel"));
        musicImageLabel->setMinimumSize(QSize(150, 0));
        musicImageLabel->setMaximumSize(QSize(150, 16777215));
        musicImageLabel->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(musicImageLabel);

        playAll = new QWidget(musicPlayBox);
        playAll->setObjectName(QString::fromUtf8("playAll"));
        playAll->setMinimumSize(QSize(120, 0));
        playAll->setMaximumSize(QSize(120, 16777215));
        playAll->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(playAll);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 93, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        playAllBtn = new QPushButton(playAll);
        playAllBtn->setObjectName(QString::fromUtf8("playAllBtn"));
        playAllBtn->setMinimumSize(QSize(100, 30));
        playAllBtn->setMaximumSize(QSize(100, 30));
        playAllBtn->setStyleSheet(QString::fromUtf8("#playAllBtn\n"
"{\n"
"	background-color:#E3E3E3;\n"
"	border-radius:10px;\n"
"}\n"
"\n"
"#playAllBtn:hover\n"
"{\n"
"	background-color:#1ECD97;\n"
"}"));

        verticalLayout_2->addWidget(playAllBtn);


        horizontalLayout->addWidget(playAll);

        horizontalSpacer = new QSpacerItem(521, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(musicPlayBox);

        listLabelBox = new QWidget(CommonPage);
        listLabelBox->setObjectName(QString::fromUtf8("listLabelBox"));
        listLabelBox->setMinimumSize(QSize(0, 40));
        listLabelBox->setMaximumSize(QSize(16777215, 40));
        listLabelBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(listLabelBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        musicNameLabel = new QLabel(listLabelBox);
        musicNameLabel->setObjectName(QString::fromUtf8("musicNameLabel"));

        horizontalLayout_2->addWidget(musicNameLabel);

        musicSingerLabel = new QLabel(listLabelBox);
        musicSingerLabel->setObjectName(QString::fromUtf8("musicSingerLabel"));

        horizontalLayout_2->addWidget(musicSingerLabel);

        musicAlbumLabel = new QLabel(listLabelBox);
        musicAlbumLabel->setObjectName(QString::fromUtf8("musicAlbumLabel"));

        horizontalLayout_2->addWidget(musicAlbumLabel);


        verticalLayout->addWidget(listLabelBox);

        pageMusicList = new QListWidget(CommonPage);
        pageMusicList->setObjectName(QString::fromUtf8("pageMusicList"));

        verticalLayout->addWidget(pageMusicList);


        retranslateUi(CommonPage);

        QMetaObject::connectSlotsByName(CommonPage);
    } // setupUi

    void retranslateUi(QWidget *CommonPage)
    {
        CommonPage->setWindowTitle(QCoreApplication::translate("CommonPage", "Form", nullptr));
        PageTittle->setText(QCoreApplication::translate("CommonPage", "\346\234\254\345\234\260\351\237\263\344\271\220", nullptr));
        musicImageLabel->setText(QCoreApplication::translate("CommonPage", "\345\233\276\347\211\207", nullptr));
        playAllBtn->setText(QCoreApplication::translate("CommonPage", "\346\222\255\346\224\276\345\205\250\351\203\250", nullptr));
        musicNameLabel->setText(QCoreApplication::translate("CommonPage", "\346\255\214\346\233\262\345\220\215\347\247\260", nullptr));
        musicSingerLabel->setText(QCoreApplication::translate("CommonPage", "\346\255\214\346\211\213\345\220\215\347\247\260", nullptr));
        musicAlbumLabel->setText(QCoreApplication::translate("CommonPage", "\344\270\223\350\276\221\345\220\215\347\247\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CommonPage: public Ui_CommonPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONPAGE_H
