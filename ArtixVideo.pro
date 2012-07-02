#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T19:42:09
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArtixVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlreader.cpp

HEADERS  += mainwindow.h \
    xmlreader.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Queries.xml
