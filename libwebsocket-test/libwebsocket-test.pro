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

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../lib

QMAKE_CLEAN += -r $${PWD}/$${DESTDIR}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lhttpdecoder
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhttpdecoder
else:unix: LIBS += -L$$PWD/../lib/ -lhttpdecoder

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libwebsocket/release/release/ -lwebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libwebsocket/release/debug/ -lwebsocket
else:unix: LIBS += -L$$PWD/../libwebsocket/release/ -lwebsocket

INCLUDEPATH += $$PWD/../libwebsocket/release
DEPENDPATH += $$PWD/../libwebsocket/release
