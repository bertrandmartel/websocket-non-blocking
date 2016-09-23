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

INCLUDEPATH += $$PWD/../http-streaming-decoder/httpdecoder/release
LIBS += -L$$PWD/../http-streaming-decoder/httpdecoder/release -lhttpdecoder
DEPENDPATH += $$PWD/../http-streaming-decoder/httpdecoder/release

QMAKE_CLEAN += -r $${PWD}/$${DESTDIR}

QMAKE_POST_LINK +=$$quote(rsync -avm --include=*/ --include=*.h --exclude=* $${PWD}/$${SOURCES_DIR}/ $${PWD}/$${DESTDIR})
