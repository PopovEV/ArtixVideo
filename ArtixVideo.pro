#-------------------------------------------------
#
# Project created by QtCreator 2012-07-01T19:42:09
#
#-------------------------------------------------

QT       += core gui xml sql phonon network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArtixVideo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sql.cpp \
    xmlreader.cpp \
    longintvalidator.cpp \
    currencyvalidator.cpp \
    mediaplayer.cpp

HEADERS  += mainwindow.h \
    sql.h \
    xmlreader.h \
    longintvalidator.h \
    currencyvalidator.h \
    mediaplayer.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    Queries.xml
