QT += core gui widgets multimedia testlib
CONFIG += c++11 testcase
TEMPLATE = app
TARGET = qqmusic_tests

SOURCES += tests/test_p0.cpp \
           lrcpage.cpp \
           recbox.cpp \
           recboxitem.cpp

HEADERS += lrcpage.h \
           recbox.h \
           recboxitem.h

FORMS += lrcpage.ui \
         recbox.ui \
         recboxitem.ui

UI_DIR = test-build/ui
MOC_DIR = test-build/moc
OBJECTS_DIR = test-build/obj
RCC_DIR = test-build/rcc
DESTDIR = test-build/bin
