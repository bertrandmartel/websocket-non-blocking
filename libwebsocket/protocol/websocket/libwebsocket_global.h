/**
    libwebsocket_global.h

    declare the function defined as LIBWEBSOCKET_LIBRARY to be exported as a shared library

    @author Bertrand Martel
    @version 1.0
*/
#ifndef LIBWEBSOCKET_GLOBAL_H
#define LIBWEBSOCKET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBWEBSOCKET_LIBRARY)
#  define LIBWEBSOCKETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LIBWEBSOCKETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBWEBSOCKET_GLOBAL_H
