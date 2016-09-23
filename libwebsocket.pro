TEMPLATE = subdirs
SUBDIRS = http-streaming-decoder libwebsocket libwebsocket-test
libwebsocket.depends = http-streaming-decoder
libwebsocket-test.depends = libwebsocket