/**
    websocketprotocol.h

    Websocket protocol constants see https://tools.ietf.org/html/rfc6455

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETPROTOCOL_H
#define WEBSOCKETPROTOCOL_H

/** FIN_FRAME mask */
#define WEBSOCKET_PROTOCOL_FIN 0b10000000

/** RSV_FRAME mask */
#define WEBSOCKET_PROTOCOL_RSV 0b01110000

/** OPCODE_FRAME mask */
#define WEBSOCKET_PROTOCOL_OPCODE 0b00001111

/** MASK_FRAME mask */
#define WEBSOCKET_PROTOCOL_MASK 0b10000000

/** PAYLOAD_LENGTH mask */
#define WEBSOCKET_PROTOCOL_PAYLOAD_LENGTH  0b01111111

/** static size for 2 byte data payload */
#define WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_2BYTES 2

/** static size for 8 bytes data payload */
#define WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_8BYTES 8

/** mask key size is always 4 (only when mask is enabled) */
#define WEBSOCKET_PROTOCOL_MASK_KEY_SIZE 4

/**
 * if payload size < payload_size_limit1 payload_length_frame is actual
 * payload length value || if payload size > payload_size_limit1 payload
 * length value is following two byte after PAYLOAD_LENGTH_FRAME
 */
#define WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT1 126

/**
 * if payload size is PAYLOAD_SIZE_LIMIT2 following 8 bytes are actual
 * paylad length value
 */
#define WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT2 127

#endif // WEBSOCKETPROTOCOL_H
