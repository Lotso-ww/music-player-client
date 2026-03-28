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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LrcPage
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *bgStyle;
    QVBoxLayout *verticalLayout;
    QWidget *lrcTop;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *hideBtn;
    QWidget *titltBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *musicSinger;
    QLabel *musicName;
    QWidget *lrcContent;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QLabel *line1;
    QLabel *line2;
    QLabel *line3;
    QLabel *lineCenter;
    QLabel *line4;
    QLabel *line5;
    QLabel *line6;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *LrcPage)
    {
        if (LrcPage->objectName().isEmpty())
            LrcPage->setObjectName(QString::fromUtf8("LrcPage"));
        LrcPage->resize(1020, 680);
        horizontalLayout = new QHBoxLayout(LrcPage);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        bgStyle = new QWidget(LrcPage);
        bgStyle->setObjectName(QString::fromUtf8("bgStyle"));
        bgStyle->setStyleSheet(QString::fromUtf8("#bgStyle\n"
"{\n"
"	border-image:url(\":/images/bg.png\");\n"
"}\n"
"*\n"
"{\n"
"	color: #FFFFFF;\n"
"}"));
        verticalLayout = new QVBoxLayout(bgStyle);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lrcTop = new QWidget(bgStyle);
        lrcTop->setObjectName(QString::fromUtf8("lrcTop"));
        lrcTop->setMinimumSize(QSize(0, 50));
        lrcTop->setMaximumSize(QSize(16777215, 50));
        lrcTop->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(lrcTop);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 0, 0);
        hideBtn = new QPushButton(lrcTop);
        hideBtn->setObjectName(QString::fromUtf8("hideBtn"));
        hideBtn->setMinimumSize(QSize(30, 50));
        hideBtn->setMaximumSize(QSize(30, 50));
        hideBtn->setStyleSheet(QString::fromUtf8("#hideBtn\n"
"{\n"
"	border: none;\n"
"}"));

        horizontalLayout_2->addWidget(hideBtn);

        titltBox = new QWidget(lrcTop);
        titltBox->setObjectName(QString::fromUtf8("titltBox"));
        titltBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(titltBox);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        musicSinger = new QLabel(titltBox);
        musicSinger->setObjectName(QString::fromUtf8("musicSinger"));
        musicSinger->setStyleSheet(QString::fromUtf8(""));
        musicSinger->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(musicSinger);

        musicName = new QLabel(titltBox);
        musicName->setObjectName(QString::fromUtf8("musicName"));
        musicName->setStyleSheet(QString::fromUtf8(""));
        musicName->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(musicName);


        horizontalLayout_2->addWidget(titltBox);


        verticalLayout->addWidget(lrcTop);

        lrcContent = new QWidget(bgStyle);
        lrcContent->setObjectName(QString::fromUtf8("lrcContent"));
        lrcContent->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(lrcContent);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 122, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        line1 = new QLabel(lrcContent);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setMinimumSize(QSize(0, 50));
        line1->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(15);
        line1->setFont(font);
        line1->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line1);

        line2 = new QLabel(lrcContent);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setMinimumSize(QSize(0, 50));
        line2->setMaximumSize(QSize(16777215, 50));
        line2->setFont(font);
        line2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line2);

        line3 = new QLabel(lrcContent);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setMinimumSize(QSize(0, 50));
        line3->setMaximumSize(QSize(16777215, 50));
        line3->setFont(font);
        line3->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line3);

        lineCenter = new QLabel(lrcContent);
        lineCenter->setObjectName(QString::fromUtf8("lineCenter"));
        lineCenter->setMinimumSize(QSize(0, 80));
        lineCenter->setMaximumSize(QSize(16777215, 80));
        QFont font1;
        font1.setPointSize(25);
        lineCenter->setFont(font1);
        lineCenter->setStyleSheet(QString::fromUtf8("#lineCenter\n"
"{\n"
"	color: #1ECE9A;\n"
"}"));
        lineCenter->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(lineCenter);

        line4 = new QLabel(lrcContent);
        line4->setObjectName(QString::fromUtf8("line4"));
        line4->setMinimumSize(QSize(0, 50));
        line4->setMaximumSize(QSize(16777215, 50));
        line4->setFont(font);
        line4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line4);

        line5 = new QLabel(lrcContent);
        line5->setObjectName(QString::fromUtf8("line5"));
        line5->setMinimumSize(QSize(0, 50));
        line5->setMaximumSize(QSize(16777215, 50));
        line5->setFont(font);
        line5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line5);

        line6 = new QLabel(lrcContent);
        line6->setObjectName(QString::fromUtf8("line6"));
        line6->setMinimumSize(QSize(0, 50));
        line6->setMaximumSize(QSize(16777215, 50));
        line6->setFont(font);
        line6->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(line6);

        verticalSpacer_2 = new QSpacerItem(20, 122, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout->addWidget(lrcContent);


        horizontalLayout->addWidget(bgStyle);


        retranslateUi(LrcPage);

        QMetaObject::connectSlotsByName(LrcPage);
    } // setupUi

    void retranslateUi(QWidget *LrcPage)
    {
        LrcPage->setWindowTitle(QCoreApplication::translate("LrcPage", "Form", nullptr));
        hideBtn->setText(QString());
        musicSinger->setText(QCoreApplication::translate("LrcPage", "\345\210\200\351\203\216", nullptr));
        musicName->setText(QCoreApplication::translate("LrcPage", "2002\345\271\264\347\232\204\347\254\254\344\270\200\345\234\272\351\233\252", nullptr));
        line1->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        line2->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        line3->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        lineCenter->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        line4->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        line5->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
        line6->setText(QCoreApplication::translate("LrcPage", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LrcPage: public Ui_LrcPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LRCPAGE_H
