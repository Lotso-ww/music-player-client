/********************************************************************************
** Form generated from reading UI file 'listitembox.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTITEMBOX_H
#define UI_LISTITEMBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListItemBox
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *musicNameBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *likeBtn;
    QLabel *musicNameLabel;
    QLabel *VIPLabel;
    QLabel *SQLabel;
    QSpacerItem *horizontalSpacer;
    QWidget *musicSingerBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *musicSingerLabel;
    QWidget *musicAlbumBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *musicAlbumLabel;

    void setupUi(QWidget *ListItemBox)
    {
        if (ListItemBox->objectName().isEmpty())
            ListItemBox->setObjectName(QString::fromUtf8("ListItemBox"));
        ListItemBox->resize(800, 45);
        horizontalLayout = new QHBoxLayout(ListItemBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        musicNameBox = new QWidget(ListItemBox);
        musicNameBox->setObjectName(QString::fromUtf8("musicNameBox"));
        musicNameBox->setMinimumSize(QSize(410, 0));
        musicNameBox->setMaximumSize(QSize(410, 16777215));
        musicNameBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(musicNameBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        likeBtn = new QPushButton(musicNameBox);
        likeBtn->setObjectName(QString::fromUtf8("likeBtn"));
        likeBtn->setMinimumSize(QSize(25, 25));
        likeBtn->setMaximumSize(QSize(25, 25));
        likeBtn->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(likeBtn);

        musicNameLabel = new QLabel(musicNameBox);
        musicNameLabel->setObjectName(QString::fromUtf8("musicNameLabel"));
        musicNameLabel->setMinimumSize(QSize(130, 0));
        musicNameLabel->setMaximumSize(QSize(130, 16777215));

        horizontalLayout_2->addWidget(musicNameLabel);

        VIPLabel = new QLabel(musicNameBox);
        VIPLabel->setObjectName(QString::fromUtf8("VIPLabel"));
        VIPLabel->setMinimumSize(QSize(30, 0));
        VIPLabel->setMaximumSize(QSize(30, 15));
        VIPLabel->setStyleSheet(QString::fromUtf8("#VIPLabel\n"
"{\n"
"	borderr: 1px solid #1ECD96;\n"
"	color: #1ECD96;\n"
"	border-radius: 2px;\n"
"}"));

        horizontalLayout_2->addWidget(VIPLabel);

        SQLabel = new QLabel(musicNameBox);
        SQLabel->setObjectName(QString::fromUtf8("SQLabel"));
        SQLabel->setMinimumSize(QSize(30, 0));
        SQLabel->setMaximumSize(QSize(30, 15));
        SQLabel->setStyleSheet(QString::fromUtf8("#SQLabel\n"
"{\n"
"	borderr: 1px solid #FF6600;\n"
"	color: #FF6600;\n"
"	border-radius: 2px;\n"
"}"));

        horizontalLayout_2->addWidget(SQLabel);

        horizontalSpacer = new QSpacerItem(162, 6, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        horizontalLayout->addWidget(musicNameBox);

        musicSingerBox = new QWidget(ListItemBox);
        musicSingerBox->setObjectName(QString::fromUtf8("musicSingerBox"));
        musicSingerBox->setMinimumSize(QSize(150, 0));
        musicSingerBox->setMaximumSize(QSize(150, 16777215));
        musicSingerBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(musicSingerBox);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        musicSingerLabel = new QLabel(musicSingerBox);
        musicSingerLabel->setObjectName(QString::fromUtf8("musicSingerLabel"));

        horizontalLayout_4->addWidget(musicSingerLabel);


        horizontalLayout->addWidget(musicSingerBox);

        musicAlbumBox = new QWidget(ListItemBox);
        musicAlbumBox->setObjectName(QString::fromUtf8("musicAlbumBox"));
        musicAlbumBox->setMinimumSize(QSize(235, 0));
        musicAlbumBox->setMaximumSize(QSize(235, 16777215));
        musicAlbumBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_3 = new QHBoxLayout(musicAlbumBox);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        musicAlbumLabel = new QLabel(musicAlbumBox);
        musicAlbumLabel->setObjectName(QString::fromUtf8("musicAlbumLabel"));

        horizontalLayout_3->addWidget(musicAlbumLabel);


        horizontalLayout->addWidget(musicAlbumBox);


        retranslateUi(ListItemBox);

        QMetaObject::connectSlotsByName(ListItemBox);
    } // setupUi

    void retranslateUi(QWidget *ListItemBox)
    {
        ListItemBox->setWindowTitle(QCoreApplication::translate("ListItemBox", "Form", nullptr));
        likeBtn->setText(QString());
        musicNameLabel->setText(QCoreApplication::translate("ListItemBox", "\345\217\257\345\217\257\346\211\230\346\265\267\347\232\204\347\211\247\347\276\212\344\272\272", nullptr));
        VIPLabel->setText(QCoreApplication::translate("ListItemBox", "VIP", nullptr));
        SQLabel->setText(QCoreApplication::translate("ListItemBox", "SQ", nullptr));
        musicSingerLabel->setText(QCoreApplication::translate("ListItemBox", "\347\216\213\347\220\246", nullptr));
        musicAlbumLabel->setText(QCoreApplication::translate("ListItemBox", "\345\217\257\345\217\257\346\211\230\346\265\267\347\232\204\347\211\247\347\276\212\344\272\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListItemBox: public Ui_ListItemBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTITEMBOX_H
