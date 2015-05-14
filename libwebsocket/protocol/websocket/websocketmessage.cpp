/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Bertrand Martel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "websocketmessage.h"
#include <QByteArray>
#include "websocketprotocol.h"
#include <QDebug>
using namespace std;

/**
 * @brief WebSocketMessage::WebSocketMessage
 *      Build generic websocket message (init all var to 0)
 */
WebSocketMessage::WebSocketMessage()
{
    FIN_FRAME=0;
    RSV_FRAME=0;
    OPCODE_FRAME=0;
    MASK_FRAME=0;
    PAYLOAD_LENGTH_FRAME=0;
    payloadLengthValue=0;
    opcodeType=0;
    maskKey=0;
    payloadData=0;
    payloadLength=0;
}

/**
 * @brief WebSocketMessage::WebSocketMessage
 *      websocket message construct for sending a basic QByteArray message to websocket
 * @param payloadData
 *      data to send
 */
WebSocketMessage::WebSocketMessage(QByteArray payloadData)
{
    this->FIN_FRAME = 1;
    this->RSV_FRAME = 0;
    this->OPCODE_FRAME = 1;
    this->MASK_FRAME = 0;
    this->payloadData = payloadData;
}

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
WebSocketMessage::WebSocketMessage(int FIN_FRAME, int RSV_FRAME, int OPCODE_FRAME,
        int MASK_FRAME,QByteArray maskKey, QByteArray payloadData) {
    this->FIN_FRAME = FIN_FRAME;
    this->RSV_FRAME = RSV_FRAME;
    this->OPCODE_FRAME = OPCODE_FRAME;
    this->MASK_FRAME = MASK_FRAME;
    if (maskKey != nullptr) {
        this->maskKey = maskKey;
    }
    this->payloadData = payloadData;
}

/**
 * Build a message according to all information gathered in websocket
 * message object
 *
 * @return byte array to be sent to outputstream
 * */
QByteArray WebSocketMessage::buildMessage() {    int mask_size = 0;
    int lengthIndicator = 0;
    QByteArray lengthSize;

    if (this->MASK_FRAME == 0x01) {
        mask_size = WEBSOCKET_PROTOCOL_MASK_KEY_SIZE;
    }

    /* offset for number of bytes defining length */

    /* FFFF = 65536 => 8 bytes for payload data length */
    if (this->payloadData.length() > 65535) {

        QByteArray array(8,0);
        lengthIndicator = WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT2;
        int left = this->payloadData.length();
        int unit = 256;
        for (int i = 8; i > 0; i--) {
            array[i - 1] =  (left % unit);
            left = left / unit;

            if (left == 0)
                break;
        }
        lengthSize[0]=array[0];
        lengthSize[1]=array[1];
        lengthSize[2]=array[2];
        lengthSize[3]=array[3];
        lengthSize[4]=array[4];
        lengthSize[5]=array[5];
        lengthSize[6]=array[6];
        lengthSize[7]=array[7];

    } else if (this->payloadData.length() > 125) {
        /* 01111111 == 127 max */
        QByteArray array(2,0);
        array[0] =  (this->payloadData.length() >> 8);
        array[1] = (this->payloadData.length() >> 0);

        lengthIndicator = WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT1;
        lengthSize[0]=array[0];
        lengthSize[1]=array[1];
    }
    else
    {
        lengthIndicator = this->payloadData.length();
        lengthSize = 0;
    }

    QByteArray message = QByteArray(1 + 1 + lengthSize.length() + mask_size
            + this->payloadData.length(),0);

    message[0] =  ((this->FIN_FRAME << 7) + (this->RSV_FRAME << 4) + (this->OPCODE_FRAME));
    message[1] = ((this->MASK_FRAME << 7) + lengthIndicator);

    for (int i = 0; i < lengthSize.length(); i++) {
        message[i + 2] = lengthSize[i];
    }
    if (mask_size != 0) {
        message[2 + lengthSize.length()] = this->maskKey[0];
        message[2 + lengthSize.length() + 1] = this->maskKey[1];
        message[2 + lengthSize.length() + 2] = this->maskKey[2];
        message[2 + lengthSize.length() + 3] = this->maskKey[3];

        for (int i = 2 + lengthSize.length() + 4; i  < 2 + lengthSize.length() + 4+this->payloadData.length();i++)
        {
            message[i]=this->payloadData[i-(2 + lengthSize.length() + 4)];
        }
    } else {
        for (int i = 2 + lengthSize.length(); i  < 2 + lengthSize.length()+this->payloadData.length();i++)
        {
            message[i]=this->payloadData[i-(2 + lengthSize.length())];
        }
    }
    return message;
}

/**
 * Display some information in console
 */
string WebSocketMessage::toString() {
    string ret = FIN_FRAME + " message(s) - ";
    ret+= opcodeType + " -  ";
    if (MASK_FRAME == 1) {
        ret += " PAYLOAD DATA IS MASKED";
    } else {
        ret += " PAYLOAD DATA IS NOT MASKED";
    }
    ret += " - PAYLOAD LENGTH : " + this->payloadLengthValue;
    return ret;
}

/**
 * Getter for FIN_FRAME value
 *
 * @return FIN_FRAME value
 */
int WebSocketMessage::getFIN() {
    return FIN_FRAME;
}

/**
 * Set FIN_FRAME value
 *
 * @param fIN
 *            fin byte value
 */
void WebSocketMessage::setFIN(int fIN) {
    FIN_FRAME = (fIN >> 7);
}

/**
 * Retrieve RSV byte array value
 *
 * @return RSV_FRAME
 */
int WebSocketMessage::getRSV() {
    return RSV_FRAME;
}

/**
 * Set RSV byte array value
 *
 * @param rSV
 *            RSV_FRAME
 */
void WebSocketMessage::setRSV(int rSV) {
    RSV_FRAME = (rSV >> 4);
}

/**
 * Retrieve Opcode value
 *
 * @return opcode frame value
 */
int WebSocketMessage::getOPCODE() {
    return OPCODE_FRAME;
}

/**
 * Set opcode value ofr OPCODE_FRAME
 *
 * @param oPCODE
 *            opcode byte integer value
 */
void WebSocketMessage::setOPCODE(int oPCODE) {
    OPCODE_FRAME = oPCODE;
}

/**
 * Opcode frame type
 *
 * @return opcode type according to opcode type class
 */
int WebSocketMessage::getOpcodeType() {
    return opcodeType;
}

void WebSocketMessage::setOpcodeType(int opcodeType) {
    this->opcodeType = opcodeType;
}

/**
 * Get mask value (1 for data payload masked and 0 for not being masked)
 *
 * @return MASK_FRAME value
 */
int WebSocketMessage::getMASK() {
    return MASK_FRAME;
}

/**
 * Set mask value
 *
 * @param mASK
 *            MASK8FRAME value
 */
void WebSocketMessage::setMASK(int mASK) {
    MASK_FRAME = (mASK >> 7);
}

/**
 * Retrieve PAYLOAD_LENTH_FRAME value (actual byte being read but not the
 * ACTUAL length of data payload (only if PAYLOAD_LENGTH_FRAME <126 cf
 * protocol))
 *
 * @return Data payload frame value
 */
int WebSocketMessage::getPAYLOAD_LENGTH_FRAME() {
    return PAYLOAD_LENGTH_FRAME;
}

/**
 * Set value for data payload frame
 *
 * @param PAYLOAD_LENGTH_FRAME
 *            data payload length value
 */
void WebSocketMessage::setPAYLOAD_LENGTH_FRAME(int PAYLOAD_LENGTH_FRAME) {
    this->PAYLOAD_LENGTH_FRAME = PAYLOAD_LENGTH_FRAME;
}

/**
 * Retrieve actual length of data payload (in number of octets)
 *
 * @return number of octet of data payload
 */
int WebSocketMessage::getPayload_length() {
    return payloadLengthValue;
}

/**
 * Set data payload length value with integer parameter
 *
 * @param payload_length
 *            payload length actual value
 */
void WebSocketMessage::setPayload_length(int payload_length) {
    this->payloadLengthValue = payload_length;
}

/**
 * Set data payload length with a byte array as parameters
 *
 * @param payload_length
 *            data payload length byte array
 */
void WebSocketMessage::setPayload_length(QByteArray payload_length) {
    int length = 0;
    for (int i = 0; i < payload_length.length(); i++) {
        length += (payload_length[i] & 0xFF) << (8 * (payload_length.length()
                - i - 1));
    }
    this->payloadLengthValue = length;
}

