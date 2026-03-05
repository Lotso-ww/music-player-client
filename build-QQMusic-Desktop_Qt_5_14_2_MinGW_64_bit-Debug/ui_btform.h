/********************************************************************************
** Form generated from reading UI file 'btform.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BTFORM_H
#define UI_BTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_btForm
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *btStyle;
    QHBoxLayout *horizontalLayout_2;
    QLabel *btIcon;
    QLabel *btText;
    QWidget *lineBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *line1;
    QLabel *line2;
    QLabel *line3;
    QLabel *line4;

    void setupUi(QWidget *btForm)
    {
        if (btForm->objectName().isEmpty())
            btForm->setObjectName(QString::fromUtf8("btForm"));
        btForm->resize(200, 35);
        horizontalLayout = new QHBoxLayout(btForm);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        btStyle = new QWidget(btForm);
        btStyle->setObjectName(QString::fromUtf8("btStyle"));
        btStyle->setStyleSheet(QString::fromUtf8("#btStyle:hover\n"
"{\n"
"	background-color:#D8D8D8;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(btStyle);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btIcon = new QLabel(btStyle);
        btIcon->setObjectName(QString::fromUtf8("btIcon"));
        btIcon->setMinimumSize(QSize(30, 0));
        btIcon->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(btIcon);

        btText = new QLabel(btStyle);
        btText->setObjectName(QString::fromUtf8("btText"));
        btText->setMinimumSize(QSize(128, 0));
        btText->setMaximumSize(QSize(128, 16777215));

        horizontalLayout_2->addWidget(btText);

        lineBox = new QWidget(btStyle);
        lineBox->setObjectName(QString::fromUtf8("lineBox"));
        lineBox->setMinimumSize(QSize(45, 0));
        lineBox->setMaximumSize(QSize(45, 16777215));
        lineBox->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	background-color:#FFFFFF;\n"
"}\n"
""));
        horizontalLayout_3 = new QHBoxLayout(lineBox);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        line1 = new QLabel(lineBox);
        line1->setObjectName(QString::fromUtf8("line1"));
        line1->setEnabled(true);
        line1->setMinimumSize(QSize(2, 15));
        line1->setMaximumSize(QSize(2, 15));

        horizontalLayout_3->addWidget(line1);

        line2 = new QLabel(lineBox);
        line2->setObjectName(QString::fromUtf8("line2"));
        line2->setMinimumSize(QSize(2, 15));
        line2->setMaximumSize(QSize(2, 15));

        horizontalLayout_3->addWidget(line2);

        line3 = new QLabel(lineBox);
        line3->setObjectName(QString::fromUtf8("line3"));
        line3->setMinimumSize(QSize(2, 15));
        line3->setMaximumSize(QSize(2, 15));

        horizontalLayout_3->addWidget(line3);

        line4 = new QLabel(lineBox);
        line4->setObjectName(QString::fromUtf8("line4"));
        line4->setMinimumSize(QSize(2, 15));
        line4->setMaximumSize(QSize(2, 15));

        horizontalLayout_3->addWidget(line4);


        horizontalLayout_2->addWidget(lineBox);


        horizontalLayout->addWidget(btStyle);


        retranslateUi(btForm);

        QMetaObject::connectSlotsByName(btForm);
    } // setupUi

    void retranslateUi(QWidget *btForm)
    {
        btForm->setWindowTitle(QCoreApplication::translate("btForm", "Form", nullptr));
        btIcon->setText(QCoreApplication::translate("btForm", "\345\233\276", nullptr));
        btText->setText(QCoreApplication::translate("btForm", "\346\234\254\345\234\260\351\237\263\344\271\220", nullptr));
        line1->setText(QString());
        line2->setText(QString());
        line3->setText(QString());
        line4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class btForm: public Ui_btForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BTFORM_H
