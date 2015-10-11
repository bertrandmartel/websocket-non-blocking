#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T16:08:36
#
#-------------------------------------------------

QT       += network
QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x
CONFIG+= staticlib
CONFIG+= qt debug

DESTDIR = release

OBJECTS_DIR=bin

TARGET = websocket
TEMPLATE = lib

SOURCES += protocol/websocket/*.cpp \
           utils/*.cpp \
           crypto/*.cpp

HEADERS += protocol/websocket/*.h \
        utils/*.h \
        crypto/*.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/release/ -lhttpdecoder
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/debug/ -lhttpdecoder
else:unix: LIBS += -L$$PWD/../libs/ -lhttpdecoder

INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libs

QMAKE_CLEAN += -r $${PWD}/$${DESTDIR}

QMAKE_POST_LINK +=$$quote(rsync -avm --include=*/ --include=*.h --exclude=* $${PWD}/$${SOURCES_DIR}/ $${PWD}/$${DESTDIR})
