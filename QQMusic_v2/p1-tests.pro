QT += core gui widgets multimedia sql testlib
CONFIG += c++11 testcase
TEMPLATE = app
TARGET = qqmusic_p1_tests

SOURCES += tests/test_p1.cpp \
           localsearchservice.cpp \
           music.cpp \
           musiclist.cpp \
           musicscanner.cpp \
           thememanager.cpp

HEADERS += localsearchservice.h \
           music.h \
           musiclist.h \
           musicscanner.h \
           thememanager.h

UI_DIR = test-build/p1-ui
MOC_DIR = test-build/p1-moc
OBJECTS_DIR = test-build/p1-obj
RCC_DIR = test-build/p1-rcc
DESTDIR = test-build/bin
