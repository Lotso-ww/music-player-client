/********************************************************************************
** Form generated from reading UI file 'volumetool.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUMETOOL_H
#define UI_VOLUMETOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VolumeTool
{
public:
    QWidget *volumeWidget;
    QPushButton *silenceBtn;
    QLabel *volumeRatio;
    QWidget *volumeBox;
    QFrame *inSlider;
    QFrame *outSlider;
    QPushButton *sliderBtn;

    void setupUi(QWidget *VolumeTool)
    {
        if (VolumeTool->objectName().isEmpty())
            VolumeTool->setObjectName(QString::fromUtf8("VolumeTool"));
        VolumeTool->resize(100, 350);
        volumeWidget = new QWidget(VolumeTool);
        volumeWidget->setObjectName(QString::fromUtf8("volumeWidget"));
        volumeWidget->setGeometry(QRect(10, 10, 80, 300));
        volumeWidget->setStyleSheet(QString::fromUtf8("#volumeWidget\n"
"{\n"
"	background-color:#FFFFFF;\n"
"	border-radius:5px;\n"
"}"));
        silenceBtn = new QPushButton(volumeWidget);
        silenceBtn->setObjectName(QString::fromUtf8("silenceBtn"));
        silenceBtn->setGeometry(QRect(0, 255, 80, 45));
        silenceBtn->setMinimumSize(QSize(80, 45));
        silenceBtn->setMaximumSize(QSize(80, 45));
        silenceBtn->setStyleSheet(QString::fromUtf8("#silenceBtn\n"
"{\n"
"	border:none;\n"
"}\n"
"\n"
"#silenceBtn:hover\n"
"{\n"
"	background-color:#E0E0E0;\n"
"}"));
        volumeRatio = new QLabel(volumeWidget);
        volumeRatio->setObjectName(QString::fromUtf8("volumeRatio"));
        volumeRatio->setGeometry(QRect(0, 225, 80, 30));
        volumeRatio->setMinimumSize(QSize(0, 30));
        volumeRatio->setMaximumSize(QSize(16777215, 30));
        volumeRatio->setStyleSheet(QString::fromUtf8(""));
        volumeRatio->setAlignment(Qt::AlignCenter);
        volumeBox = new QWidget(volumeWidget);
        volumeBox->setObjectName(QString::fromUtf8("volumeBox"));
        volumeBox->setGeometry(QRect(0, 0, 80, 225));
        volumeBox->setStyleSheet(QString::fromUtf8(""));
        inSlider = new QFrame(volumeBox);
        inSlider->setObjectName(QString::fromUtf8("inSlider"));
        inSlider->setGeometry(QRect(38, 25, 4, 180));
        inSlider->setStyleSheet(QString::fromUtf8("#inSlider\n"
"{\n"
"	background-color:#ECECEC;\n"
"}"));
        inSlider->setFrameShape(QFrame::StyledPanel);
        inSlider->setFrameShadow(QFrame::Raised);
        outSlider = new QFrame(volumeBox);
        outSlider->setObjectName(QString::fromUtf8("outSlider"));
        outSlider->setGeometry(QRect(38, 25, 4, 180));
        outSlider->setStyleSheet(QString::fromUtf8("#outSlider\n"
"{\n"
"	background-color:#1ECC94;\n"
"}"));
        outSlider->setFrameShape(QFrame::StyledPanel);
        outSlider->setFrameShadow(QFrame::Raised);
        sliderBtn = new QPushButton(volumeBox);
        sliderBtn->setObjectName(QString::fromUtf8("sliderBtn"));
        sliderBtn->setGeometry(QRect(33, 20, 14, 14));
        sliderBtn->setMinimumSize(QSize(14, 14));
        sliderBtn->setMaximumSize(QSize(14, 14));
        sliderBtn->setStyleSheet(QString::fromUtf8("#sliderBtn\n"
"{\n"
"	background-color:#1ECC94;\n"
"	border-radius:7px;\n"
"}"));

        retranslateUi(VolumeTool);

        QMetaObject::connectSlotsByName(VolumeTool);
    } // setupUi

    void retranslateUi(QWidget *VolumeTool)
    {
        VolumeTool->setWindowTitle(QCoreApplication::translate("VolumeTool", "Form", nullptr));
        silenceBtn->setText(QCoreApplication::translate("VolumeTool", "\351\235\231\351\237\263", nullptr));
        volumeRatio->setText(QCoreApplication::translate("VolumeTool", "45%", nullptr));
        sliderBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VolumeTool: public Ui_VolumeTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUMETOOL_H
