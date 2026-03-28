/********************************************************************************
** Form generated from reading UI file 'qqmusic.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQMUSIC_H
#define UI_QQMUSIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <btform.h>
#include <commonpage.h>
#include <musicslider.h>
#include <recbox.h>

QT_BEGIN_NAMESPACE

class Ui_QQMusic
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *background;
    QVBoxLayout *verticalLayout;
    QWidget *head;
    QHBoxLayout *horizontalLayout_2;
    QWidget *headLeft;
    QHBoxLayout *horizontalLayout_4;
    QLabel *logo;
    QWidget *headRight;
    QHBoxLayout *horizontalLayout_3;
    QWidget *searchBox;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *lineEdit;
    QWidget *settingBox;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *skin;
    QPushButton *max;
    QPushButton *min;
    QPushButton *quit;
    QWidget *body;
    QHBoxLayout *horizontalLayout_7;
    QWidget *bodyLeft;
    QVBoxLayout *verticalLayout_2;
    QWidget *leftBox;
    QVBoxLayout *verticalLayout_3;
    QWidget *onlineMusic;
    QVBoxLayout *verticalLayout_4;
    QLabel *onlineMusicText;
    btForm *rec;
    btForm *radio;
    btForm *music;
    QWidget *myMusic;
    QVBoxLayout *verticalLayout_5;
    QLabel *myMusicText;
    btForm *like;
    btForm *local;
    btForm *recent;
    QSpacerItem *verticalSpacer;
    QWidget *bodyRight;
    QVBoxLayout *verticalLayout_6;
    QStackedWidget *stackedWidget;
    QWidget *recPage;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_7;
    QLabel *recText;
    QLabel *recMusictext;
    RecBox *recMusicBox;
    QLabel *supplyMusicText;
    RecBox *supplyMusicBox;
    QWidget *musicpage;
    QLabel *label_2;
    QWidget *radioPage;
    QLabel *label_3;
    CommonPage *likePage;
    CommonPage *localPage;
    CommonPage *recentPage;
    MusicSlider *progressBar;
    QWidget *controlBox;
    QHBoxLayout *horizontalLayout_8;
    QWidget *play1;
    QGridLayout *gridLayout;
    QLabel *musicName;
    QLabel *musicSigner;
    QLabel *musicCover;
    QWidget *play2;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *playMode;
    QPushButton *playUp;
    QPushButton *play;
    QPushButton *playDown;
    QPushButton *volume;
    QPushButton *addLocal;
    QWidget *play3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *labelNull;
    QLabel *currentTime;
    QLabel *line;
    QLabel *totalTime;
    QPushButton *lrcWord;

    void setupUi(QWidget *QQMusic)
    {
        if (QQMusic->objectName().isEmpty())
            QQMusic->setObjectName(QString::fromUtf8("QQMusic"));
        QQMusic->resize(1040, 700);
        horizontalLayout = new QHBoxLayout(QQMusic);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        background = new QWidget(QQMusic);
        background->setObjectName(QString::fromUtf8("background"));
        background->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(background);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        head = new QWidget(background);
        head->setObjectName(QString::fromUtf8("head"));
        head->setMinimumSize(QSize(0, 80));
        head->setMaximumSize(QSize(16777215, 80));
        head->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(head);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        headLeft = new QWidget(head);
        headLeft->setObjectName(QString::fromUtf8("headLeft"));
        headLeft->setMinimumSize(QSize(200, 0));
        headLeft->setMaximumSize(QSize(200, 16777215));
        headLeft->setStyleSheet(QString::fromUtf8("#headLeft\n"
"{\n"
"	background-color:#F0F0F0; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\346\265\205\347\201\260\350\211\262*/\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(headLeft);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        logo = new QLabel(headLeft);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setStyleSheet(QString::fromUtf8("#logo\n"
"{\n"
"	background-image:url(\":/images/Logo.png\");\n"
"	background-repeat:no-repeat;/*\350\256\276\347\275\256\345\233\276\347\211\207\344\270\215\351\207\215\345\244\215*/\n"
"	background-position:center;\n"
"\n"
"}"));

        horizontalLayout_4->addWidget(logo);


        horizontalLayout_2->addWidget(headLeft);

        headRight = new QWidget(head);
        headRight->setObjectName(QString::fromUtf8("headRight"));
        headRight->setStyleSheet(QString::fromUtf8("#headRight\n"
"{\n"
"	background-color:#F5F5F5; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\344\272\256\347\201\260\350\211\262*/ \n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(headRight);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        searchBox = new QWidget(headRight);
        searchBox->setObjectName(QString::fromUtf8("searchBox"));
        searchBox->setMinimumSize(QSize(300, 0));
        searchBox->setMaximumSize(QSize(300, 16777215));
        searchBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(searchBox);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, 0, 0, 0);
        lineEdit = new QLineEdit(searchBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 35));
        lineEdit->setStyleSheet(QString::fromUtf8("#lineEdit\n"
"{\n"
"	border:none;\n"
"	background-color: #E3E3E3; /*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262*/ \n"
"	border-radius:17px; /*\350\256\276\347\275\256\345\233\233\344\270\252\342\273\206\347\232\204\345\234\206\342\273\206*/\n"
"	padding-left:17px; /*\345\206\205\351\203\250\346\226\207\345\255\227\345\210\260\350\276\271\347\232\204\350\267\235\347\246\273*/\n"
"}"));

        horizontalLayout_5->addWidget(lineEdit);


        horizontalLayout_3->addWidget(searchBox);

        settingBox = new QWidget(headRight);
        settingBox->setObjectName(QString::fromUtf8("settingBox"));
        settingBox->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border-radius:0px;\n"
"	border:none;\n"
"	background-repeat:no-repeat;\n"
"	background-position:center center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgba(220,0,0,0.5);/*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\345\215\212\351\200\217\346\230\216\347\232\204\347\272\242\350\211\262*/ \n"
"}"));
        horizontalLayout_6 = new QHBoxLayout(settingBox);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(357, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        skin = new QPushButton(settingBox);
        skin->setObjectName(QString::fromUtf8("skin"));
        skin->setMinimumSize(QSize(30, 30));
        skin->setMaximumSize(QSize(30, 30));
        skin->setStyleSheet(QString::fromUtf8("#skin\n"
"{\n"
"	background-image:url(\":/images/skin.png\");\n"
"}"));

        horizontalLayout_6->addWidget(skin);

        max = new QPushButton(settingBox);
        max->setObjectName(QString::fromUtf8("max"));
        max->setMinimumSize(QSize(30, 30));
        max->setMaximumSize(QSize(30, 30));
        max->setStyleSheet(QString::fromUtf8("#max\n"
"{\n"
"	background-image:url(\":/images/max.png\");\n"
"}"));

        horizontalLayout_6->addWidget(max);

        min = new QPushButton(settingBox);
        min->setObjectName(QString::fromUtf8("min"));
        min->setMinimumSize(QSize(30, 30));
        min->setMaximumSize(QSize(30, 30));
        min->setStyleSheet(QString::fromUtf8("#min\n"
"{\n"
"	background-image:url(\":/images/min.png\");\n"
"}"));

        horizontalLayout_6->addWidget(min);

        quit = new QPushButton(settingBox);
        quit->setObjectName(QString::fromUtf8("quit"));
        quit->setMinimumSize(QSize(30, 30));
        quit->setMaximumSize(QSize(30, 30));
        quit->setStyleSheet(QString::fromUtf8("#quit\n"
"{\n"
"	background-image:url(\":/images/quit.png\");\n"
"}"));

        horizontalLayout_6->addWidget(quit);


        horizontalLayout_3->addWidget(settingBox);


        horizontalLayout_2->addWidget(headRight);


        verticalLayout->addWidget(head);

        body = new QWidget(background);
        body->setObjectName(QString::fromUtf8("body"));
        body->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_7 = new QHBoxLayout(body);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        bodyLeft = new QWidget(body);
        bodyLeft->setObjectName(QString::fromUtf8("bodyLeft"));
        bodyLeft->setMinimumSize(QSize(200, 0));
        bodyLeft->setMaximumSize(QSize(200, 16777215));
        bodyLeft->setStyleSheet(QString::fromUtf8("#bodyLeft\n"
"{    \n"
"	background-color:#F0F0F0;/*\350\256\276\347\275\256\350\203\214\346\231\257\351\242\234\350\211\262\344\270\272\346\265\205\347\201\260\350\211\262*/ \n"
"}"));
        verticalLayout_2 = new QVBoxLayout(bodyLeft);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        leftBox = new QWidget(bodyLeft);
        leftBox->setObjectName(QString::fromUtf8("leftBox"));
        leftBox->setMinimumSize(QSize(0, 400));
        leftBox->setMaximumSize(QSize(16777215, 400));
        leftBox->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(leftBox);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        onlineMusic = new QWidget(leftBox);
        onlineMusic->setObjectName(QString::fromUtf8("onlineMusic"));
        onlineMusic->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(onlineMusic);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        onlineMusicText = new QLabel(onlineMusic);
        onlineMusicText->setObjectName(QString::fromUtf8("onlineMusicText"));

        verticalLayout_4->addWidget(onlineMusicText);

        rec = new btForm(onlineMusic);
        rec->setObjectName(QString::fromUtf8("rec"));
        rec->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(rec);

        radio = new btForm(onlineMusic);
        radio->setObjectName(QString::fromUtf8("radio"));
        radio->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(radio);

        music = new btForm(onlineMusic);
        music->setObjectName(QString::fromUtf8("music"));
        music->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_4->addWidget(music);


        verticalLayout_3->addWidget(onlineMusic);

        myMusic = new QWidget(leftBox);
        myMusic->setObjectName(QString::fromUtf8("myMusic"));
        myMusic->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_5 = new QVBoxLayout(myMusic);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        myMusicText = new QLabel(myMusic);
        myMusicText->setObjectName(QString::fromUtf8("myMusicText"));

        verticalLayout_5->addWidget(myMusicText);

        like = new btForm(myMusic);
        like->setObjectName(QString::fromUtf8("like"));
        like->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(like);

        local = new btForm(myMusic);
        local->setObjectName(QString::fromUtf8("local"));
        local->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(local);

        recent = new btForm(myMusic);
        recent->setObjectName(QString::fromUtf8("recent"));
        recent->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(recent);


        verticalLayout_3->addWidget(myMusic);


        verticalLayout_2->addWidget(leftBox);

        verticalSpacer = new QSpacerItem(20, 199, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_7->addWidget(bodyLeft);

        bodyRight = new QWidget(body);
        bodyRight->setObjectName(QString::fromUtf8("bodyRight"));
        bodyRight->setStyleSheet(QString::fromUtf8("#bodyRight\n"
"{\n"
"	background-color:#F5F5F5;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(bodyRight);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 5, 0);
        stackedWidget = new QStackedWidget(bodyRight);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        recPage = new QWidget();
        recPage->setObjectName(QString::fromUtf8("recPage"));
        scrollArea = new QScrollArea(recPage);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 808, 494));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 806, 492));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(9, -1, -1, -1);
        recText = new QLabel(scrollAreaWidgetContents);
        recText->setObjectName(QString::fromUtf8("recText"));
        recText->setMinimumSize(QSize(0, 50));
        recText->setMaximumSize(QSize(16777215, 50));
        QFont font;
        font.setPointSize(24);
        recText->setFont(font);

        verticalLayout_7->addWidget(recText);

        recMusictext = new QLabel(scrollAreaWidgetContents);
        recMusictext->setObjectName(QString::fromUtf8("recMusictext"));
        recMusictext->setMinimumSize(QSize(0, 30));
        recMusictext->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setPointSize(18);
        recMusictext->setFont(font1);

        verticalLayout_7->addWidget(recMusictext);

        recMusicBox = new RecBox(scrollAreaWidgetContents);
        recMusicBox->setObjectName(QString::fromUtf8("recMusicBox"));

        verticalLayout_7->addWidget(recMusicBox);

        supplyMusicText = new QLabel(scrollAreaWidgetContents);
        supplyMusicText->setObjectName(QString::fromUtf8("supplyMusicText"));
        supplyMusicText->setMinimumSize(QSize(0, 30));
        supplyMusicText->setMaximumSize(QSize(16777215, 30));
        supplyMusicText->setFont(font1);

        verticalLayout_7->addWidget(supplyMusicText);

        supplyMusicBox = new RecBox(scrollAreaWidgetContents);
        supplyMusicBox->setObjectName(QString::fromUtf8("supplyMusicBox"));

        verticalLayout_7->addWidget(supplyMusicBox);

        scrollArea->setWidget(scrollAreaWidgetContents);
        stackedWidget->addWidget(recPage);
        musicpage = new QWidget();
        musicpage->setObjectName(QString::fromUtf8("musicpage"));
        label_2 = new QLabel(musicpage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 240, 72, 15));
        stackedWidget->addWidget(musicpage);
        radioPage = new QWidget();
        radioPage->setObjectName(QString::fromUtf8("radioPage"));
        label_3 = new QLabel(radioPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(310, 230, 72, 15));
        stackedWidget->addWidget(radioPage);
        likePage = new CommonPage();
        likePage->setObjectName(QString::fromUtf8("likePage"));
        stackedWidget->addWidget(likePage);
        localPage = new CommonPage();
        localPage->setObjectName(QString::fromUtf8("localPage"));
        stackedWidget->addWidget(localPage);
        recentPage = new CommonPage();
        recentPage->setObjectName(QString::fromUtf8("recentPage"));
        stackedWidget->addWidget(recentPage);

        verticalLayout_6->addWidget(stackedWidget);

        progressBar = new MusicSlider(bodyRight);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(0, 40));
        progressBar->setBaseSize(QSize(0, 40));
        progressBar->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_6->addWidget(progressBar);

        controlBox = new QWidget(bodyRight);
        controlBox->setObjectName(QString::fromUtf8("controlBox"));
        controlBox->setMinimumSize(QSize(0, 60));
        controlBox->setMaximumSize(QSize(16777215, 60));
        controlBox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_8 = new QHBoxLayout(controlBox);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 5);
        play1 = new QWidget(controlBox);
        play1->setObjectName(QString::fromUtf8("play1"));
        play1->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(play1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        musicName = new QLabel(play1);
        musicName->setObjectName(QString::fromUtf8("musicName"));

        gridLayout->addWidget(musicName, 0, 1, 1, 1);

        musicSigner = new QLabel(play1);
        musicSigner->setObjectName(QString::fromUtf8("musicSigner"));

        gridLayout->addWidget(musicSigner, 1, 1, 1, 1);

        musicCover = new QLabel(play1);
        musicCover->setObjectName(QString::fromUtf8("musicCover"));
        musicCover->setMinimumSize(QSize(60, 60));
        musicCover->setMaximumSize(QSize(60, 60));

        gridLayout->addWidget(musicCover, 0, 0, 2, 1);


        horizontalLayout_8->addWidget(play1);

        play2 = new QWidget(controlBox);
        play2->setObjectName(QString::fromUtf8("play2"));
        play2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	border-radius:0px;\n"
"	border:none;\n"
"	background-repeat:no-repeat;\n"
"	background-position:center center;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgba(227,227,227,0.5);\n"
"}"));
        horizontalLayout_9 = new QHBoxLayout(play2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        playMode = new QPushButton(play2);
        playMode->setObjectName(QString::fromUtf8("playMode"));
        playMode->setMinimumSize(QSize(30, 30));
        playMode->setMaximumSize(QSize(30, 30));
        playMode->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_9->addWidget(playMode);

        playUp = new QPushButton(play2);
        playUp->setObjectName(QString::fromUtf8("playUp"));
        playUp->setMinimumSize(QSize(30, 30));
        playUp->setMaximumSize(QSize(30, 30));
        playUp->setStyleSheet(QString::fromUtf8("#playUp\n"
"{\n"
"	background-image:url(\":/images/up.png\");\n"
"}"));

        horizontalLayout_9->addWidget(playUp);

        play = new QPushButton(play2);
        play->setObjectName(QString::fromUtf8("play"));
        play->setMinimumSize(QSize(30, 30));
        play->setMaximumSize(QSize(30, 30));
        play->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_9->addWidget(play);

        playDown = new QPushButton(play2);
        playDown->setObjectName(QString::fromUtf8("playDown"));
        playDown->setMinimumSize(QSize(30, 30));
        playDown->setMaximumSize(QSize(30, 30));
        playDown->setStyleSheet(QString::fromUtf8("#playDown\n"
"{\n"
"	background-image:url(\":/images/down.png\");\n"
"}"));

        horizontalLayout_9->addWidget(playDown);

        volume = new QPushButton(play2);
        volume->setObjectName(QString::fromUtf8("volume"));
        volume->setMinimumSize(QSize(30, 30));
        volume->setMaximumSize(QSize(30, 30));
        volume->setStyleSheet(QString::fromUtf8("#volume\n"
"{\n"
"	background-image:url(\":/images/volumn.png\");\n"
"}"));

        horizontalLayout_9->addWidget(volume);

        addLocal = new QPushButton(play2);
        addLocal->setObjectName(QString::fromUtf8("addLocal"));
        addLocal->setMinimumSize(QSize(30, 30));
        addLocal->setMaximumSize(QSize(30, 30));
        addLocal->setStyleSheet(QString::fromUtf8("#addLocal\n"
"{\n"
"	background-image:url(\":/images/add.png\");\n"
"}"));

        horizontalLayout_9->addWidget(addLocal);


        horizontalLayout_8->addWidget(play2);

        play3 = new QWidget(controlBox);
        play3->setObjectName(QString::fromUtf8("play3"));
        play3->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_10 = new QHBoxLayout(play3);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        labelNull = new QLabel(play3);
        labelNull->setObjectName(QString::fromUtf8("labelNull"));
        labelNull->setMinimumSize(QSize(110, 0));
        labelNull->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_10->addWidget(labelNull);

        currentTime = new QLabel(play3);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));

        horizontalLayout_10->addWidget(currentTime);

        line = new QLabel(play3);
        line->setObjectName(QString::fromUtf8("line"));

        horizontalLayout_10->addWidget(line);

        totalTime = new QLabel(play3);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));

        horizontalLayout_10->addWidget(totalTime);

        lrcWord = new QPushButton(play3);
        lrcWord->setObjectName(QString::fromUtf8("lrcWord"));
        lrcWord->setMinimumSize(QSize(30, 30));
        lrcWord->setMaximumSize(QSize(30, 30));
        lrcWord->setStyleSheet(QString::fromUtf8("#lrcWord\n"
"{    \n"
"	border: none; /* \345\216\273\351\231\244\350\276\271\346\241\206 */     \n"
"	background-repeat:no-repeat;    \n"
"	background-position:center center;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"	background-color:rgba(220,220,220,0.5);\n"
"}"));

        horizontalLayout_10->addWidget(lrcWord);


        horizontalLayout_8->addWidget(play3);


        verticalLayout_6->addWidget(controlBox);


        horizontalLayout_7->addWidget(bodyRight);


        verticalLayout->addWidget(body);


        horizontalLayout->addWidget(background);


        retranslateUi(QQMusic);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(QQMusic);
    } // setupUi

    void retranslateUi(QWidget *QQMusic)
    {
        QQMusic->setWindowTitle(QCoreApplication::translate("QQMusic", "QQMusic", nullptr));
        logo->setText(QString());
        skin->setText(QString());
        max->setText(QString());
        min->setText(QString());
        quit->setText(QString());
        onlineMusicText->setText(QCoreApplication::translate("QQMusic", "\345\234\250\347\272\277\351\237\263\344\271\220", nullptr));
        myMusicText->setText(QCoreApplication::translate("QQMusic", "\346\210\221\347\232\204\351\237\263\344\271\220", nullptr));
        recText->setText(QCoreApplication::translate("QQMusic", "\346\216\250\350\215\220", nullptr));
        recMusictext->setText(QCoreApplication::translate("QQMusic", "\344\273\212\346\227\245\344\270\272\344\275\240\346\216\250\350\215\220", nullptr));
        supplyMusicText->setText(QCoreApplication::translate("QQMusic", "\344\275\240\347\232\204\351\237\263\344\271\220\350\241\245\347\273\231\347\253\231", nullptr));
        label_2->setText(QCoreApplication::translate("QQMusic", "page2", nullptr));
        label_3->setText(QCoreApplication::translate("QQMusic", "page3", nullptr));
        musicName->setText(QCoreApplication::translate("QQMusic", "\346\255\214\345\220\215", nullptr));
        musicSigner->setText(QCoreApplication::translate("QQMusic", "\346\255\214\346\211\213", nullptr));
        musicCover->setText(QCoreApplication::translate("QQMusic", "\345\233\276\347\211\207", nullptr));
        playMode->setText(QString());
        playUp->setText(QString());
        play->setText(QString());
        playDown->setText(QString());
        volume->setText(QString());
        addLocal->setText(QString());
        labelNull->setText(QCoreApplication::translate("QQMusic", "\345\215\240\344\275\215\347\254\246", nullptr));
        currentTime->setText(QCoreApplication::translate("QQMusic", "1:30", nullptr));
        line->setText(QCoreApplication::translate("QQMusic", " /", nullptr));
        totalTime->setText(QCoreApplication::translate("QQMusic", "4:30", nullptr));
        lrcWord->setText(QCoreApplication::translate("QQMusic", "\350\257\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QQMusic: public Ui_QQMusic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQMUSIC_H
