/**
    websocketopcode.h

    Websocket protocol opcodes featuring websocket frame types
    see https://tools.ietf.org/html/rfc6455

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETOPCODE_H
#define WEBSOCKETOPCODE_H

/** continuation frame type */
#define CONTINUATION_FRAME 0

/** text frame type */
#define TEXT_FRAME 1

/** binary frame type */
#define BINARY_FRAME 2

/** connection close frame type */
#define CONNECTION_CLOSE_FRAME 8

/** ping frame type */
#define PING_FRAME 9

/** pong frame type */
#define PONG_FRAME 10

/** non control frame type (frame value is fictive => between 0x03 and 0x07) */
#define NON_CONTROL_FRAME 0

/** control frames type (frame value is fictive => between 0x0B and 0x0F */
#define CONTROL_FRAME 0

#endif // WEBSOCKETOPCODE_H
