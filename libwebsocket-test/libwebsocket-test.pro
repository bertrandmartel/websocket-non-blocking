#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T16:41:37
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

TARGET = libwebsocket-test

DESTDIR = release

OBJECTS_DIR=bin

CONFIG   += console
CONFIG   -= app_bundle
CONFIG+= qt debug

TEMPLATE = app

SOURCES += main.cpp \
           ClientSocketHandler.cpp \
            SslHandler.cpp

HEADERS += ClientSockethandler.h \
    SslHandler.h

INCLUDEPATH += $$PWD/../lib

QMAKE_CLEAN += -r $${PWD}/$${DESTDIR}


INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libwebsocket/release/release/ -lwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libwebsocket/release/debug/ -lwebsocket
else:unix: LIBS += -L$$PWD/../libwebsocket/release/ -lwebsocket

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/ -lhttpdecoder
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/ -lhttpdecoder
else:unix: LIBS += -L$$PWD/../libs/ -lhttpdecoder

INCLUDEPATH += $$PWD/../libwebsocket/release
INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libwebsocket/release
DEPENDPATH += $$PWD/../libs
