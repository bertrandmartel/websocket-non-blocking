/**
    websocketmessage.h

    generic websocket message

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETMESSAGE_H
#define WEBSOCKETMESSAGE_H

#include <QByteArray>
#include <string>

class WebSocketMessage
{
public:

    /**
     * @brief WebSocketMessage::WebSocketMessage
     *      Build generic websocket message (init all var to 0)
     */
    WebSocketMessage();

    /**
     * Websocket builder for building a new websocket message
     *
     * @param FIN_FRAME
     *            fin frame value
     * @param RSV_FRAME
     *            rsv frame value
     * @param OPCODE_FRAME
     *            opcode frame value
     * @param MASK_FRAME
     *            mask frame value
     * @param maskKey
     *            maskey value (can be null)
     * @param payloadData
     *            payload data
     */
    WebSocketMessage(int FIN_FRAME, int RSV_FRAME, int OPCODE_FRAME,
            int MASK_FRAME, QByteArray maskKey, QByteArray payloadData);

    /**
     * @brief WebSocketMessage::WebSocketMessage
     *      websocket message construct for sending a basic QByteArray message to websocket
     * @param payloadData
     *      data to send
     */
    WebSocketMessage(QByteArray payloadData);

    QByteArray buildMessage();

    std::string toString();

    /**
     * Getter for FIN_FRAME value
     *
     * @return FIN_FRAME value
     */
    int getFIN();

    /**
     * Set FIN_FRAME value
     *
     * @param fIN
     *            fin byte value
     */
    void setFIN(int fIN);

    /**
     * Retrieve RSV byte array value
     *
     * @return RSV_FRAME
     */
    int getRSV();

    /**
     * Set RSV byte array value
     *
     * @param rSV
     *            RSV_FRAME
     */
    void setRSV(int rSV);

    /**
     * Retrieve Opcode value
     *
     * @return opcode frame value
     */
    int getOPCODE();

    /**
     * Set opcode value ofr OPCODE_FRAME
     *
     * @param oPCODE
     *            opcode byte integer value
     */
    void setOPCODE(int oPCODE);

    /**
     * Opcode frame type
     *
     * @return opcode type according to opcode type class
     */
    int getOpcodeType();

    void setOpcodeType(int opcodeType);

    /**
     * Get mask value (1 for data payload masked and 0 for not being masked)
     *
     * @return MASK_FRAME value
     */
    int getMASK();

    /**
     * Set mask value
     *
     * @param mASK
     *            MASK8FRAME value
     */
    void setMASK(int mASK);

    /**
     * Retrieve PAYLOAD_LENTH_FRAME value (actual byte being read but not the
     * ACTUAL length of data payload (only if PAYLOAD_LENGTH_FRAME <126 cf
     * protocol))
     *
     * @return Data payload frame value
     */
    int getPAYLOAD_LENGTH_FRAME();

    /**
     * Set value for data payload frame
     *
     * @param PAYLOAD_LENGTH_FRAME
     *            data payload length value
     */
    void setPAYLOAD_LENGTH_FRAME(int PAYLOAD_LENGTH_FRAME);

    /**
     * Retrieve actual length of data payload (in number of octets)
     *
     * @return number of octet of data payload
     */
    int getPayload_length();

    /**
     * Set data payload length value with integer parameter
     *
     * @param payload_length
     *            payload length actual value
     */
    void setPayload_length(int payload_length);

    /**
     * Set data payload length with a byte array as parameters
     *
     * @param payload_length
     *            data payload length byte array
     */
    void setPayload_length(QByteArray payload_length);

    /**
     * mask key for masking data payload (only if MASK_FRAME == 0x01)
     */
    QByteArray maskKey;

    /**
     * payload data
     */
    QByteArray payloadData;

    /** byte array for payload size on 2 or 8 bytes */
    QByteArray payloadLength;

private:
    /**
     * FIN frame (determine the final message)
     */
    int FIN_FRAME;

    /**
     * MUST be 0 unless an extension is negotiated that defines meanings for
     * non-zero values. If a nonzero value is received and none of the
     * negotiated extensions defines the meaning of such a nonzero value, the
     * receiving endpoint MUST _Fail the WebSocket Connection_.
     */
    int RSV_FRAME;

    /**
     * Determine the meaning of data payload see different opcode type in
     * Websocket opcode class
     */
    int OPCODE_FRAME;

    /**
     * Determine if data payload is being masked (1) or not (0)
     */
    int MASK_FRAME;

    /**
     * payload length frame value (<126 ; ==126 ; ==127)
     */
    int PAYLOAD_LENGTH_FRAME;

    /**
     * payload length actual value (in number of octet)
     */
    int payloadLengthValue;

    /**
     * opcode type object (See opcode class for full list of opcode)
     */
    int opcodeType;

};

#endif // WEBSOCKETMESSAGE_H
