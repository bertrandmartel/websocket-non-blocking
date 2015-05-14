#ifndef WEBSOCKET_H
#define WEBSOCKET_H

/**
* Initialization state
*/
#define NONE 0

/**
* Indicates that this is the final fragment in a message. The first
* fragment MAY also be the final fragment 1 byte
*/
#define FIN_STATE 1

/**
* RSV1, RSV2, RSV3: 1 bit each
*
* MUST be 0 unless an extension is negotiated that defines meanings for
* non-zero values. If a nonzero value is received and none of the
* negotiated extensions defines the meaning of such a nonzero value, the
* receiving endpoint MUST _Fail the WebSocket Connection_.
*/
#define RSV_STATE 2

/**
* Opcode: 4 bits
*
* Defines the interpretation of the "Payload data". If an unknown opcode is
* received, the receiving endpoint MUST _Fail the WebSocket Connection_.
* The following values are defined.
*
* %x0 denotes a continuation frame
*
* %x1 denotes a text frame
*
* %x2 denotes a binary frame
*
* %x3-7 are reserved for further non-control frames
*
* %x8 denotes a connection close
*
* %x9 denotes a ping
*
* %xA denotes a pong
*
* %xB-F are reserved for further control frames
*/
#define OPCODE_STATE 3

/**
* Mask: 1 bit
*
* Defines whether the "Payload data" is masked. If set to 1, a masking key
* is present in masking-key, and this is used to unmask the "Payload data"
* as per Section 5.3. All frames sent from client to server have this bit
* set to 1.
*/
#define MASK_STATE 4

/**
* Payload length: 7 bits, 7+16 bits, or 7+64 bits
*
* The length of the "Payload data", in bytes: if 0-125, that is the payload
* length. If 126, the following 2 bytes interpreted as a 16-bit unsigned
* integer are the payload length. If 127, the following 8 bytes interpreted
* as a 64-bit unsigned integer (the most significant bit MUST be 0) are the
* payload length. Multibyte length quantities are expressed in network byte
* order. Note that in all cases, the minimal number of bytes MUST be used
* to encode the length, for example, the length of a 124-byte-long string
* can't be encoded as the sequence 126, 0, 124. The payload length is the
* length of the "Extension data" + the length of the "Application data".
* The length of the "Extension data" may be zero, in which case the payload
* length is the length of the "Application data".
*/
#define PAYLOAD_LENGTH 5

/**
* state for payload length of 2 bytes size
*/
#define PAYLOAD_LENGTH_2_BYTES 6

/**
* state for payload length of 8 bytes size
*/
#define PAYLOAD_LENGTH_8_BYTES 7

/**
* Masking-key: 0 or 4 bytes
*
* All frames sent from the client to the server are masked by a 32-bit
* value that is contained within the frame. This field is present if the
* mask bit is set to 1 and is absent if the mask bit is set to 0. See
* Section 5.3 for further information on client- to-server masking.
*/
#define MASKING_KEY 8

/**
* Payload data: (x+y) bytes
*
* The "Payload data" is defined as "Extension data" concatenated with
* "Application data".
*/
#define PAYLOAD_DATA 9

/**
* Extension data: x bytes
*
* The "Extension data" is 0 bytes unless an extension has been negotiated.
* Any extension MUST specify the length of the "Extension data", or how
* that length may be calculated, and how the extension use MUST be
* negotiated during the opening handshake. If present, the "Extension data"
* is included in the total payload length.
*/
#define EXTENSION_DATA 10

/**
* Application data: y bytes
*
* Arbitrary "Application data", taking up the remainder of the frame after
* any "Extension data". The length of the "Application data" is equal to
* the payload length minus the length of the "Extension data".
*/
#define APPLICATION_DATA 11

/**
* State for end of loading data (process can start)
*/
#define FINISHED_LOADING 12

#endif // WEBSOCKET_H
