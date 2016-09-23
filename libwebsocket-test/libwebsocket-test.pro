QT       += core
QT       += network
QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x -Wno-write-strings

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

INCLUDEPATH += $$PWD/../http-streaming-decoder/httpdecoder/release
LIBS += -L$$PWD/../http-streaming-decoder/httpdecoder/release -lhttpdecoder
DEPENDPATH += $$PWD/../http-streaming-decoder/httpdecoder/release

INCLUDEPATH += $$PWD/../libwebsocket/release

DEPENDPATH += $$PWD/../libwebsocket/release
