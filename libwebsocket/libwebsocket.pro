#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T16:08:36
#
#-------------------------------------------------

QT       += network

QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

DESTDIR = release

OBJECTS_DIR=bin

TARGET = websocket
TEMPLATE = lib

DEFINES += LIBWEBSOCKET_LIBRARY

SOURCES += protocol/websocket/*.cpp \
           utils/*.cpp \
           crypto/*.cpp

HEADERS += protocol/websocket/*.h \
        utils/*.h \
        crypto/*.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lhttpdecoder
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhttpdecoder
else:unix: LIBS += -L$$PWD/../lib/ -lhttpdecoder

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib

QMAKE_CLEAN += -r $${PWD}/$${DESTDIR}

QMAKE_POST_LINK +=$$quote(rsync -avm --include=*/ --include=*.h --exclude=* $${PWD}/$${SOURCES_DIR}/ $${PWD}/$${DESTDIR})
