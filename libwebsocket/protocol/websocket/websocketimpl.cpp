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
#include "websocketimpl.h"
#include "websocketmessage.h"
#include "websocketopcode.h"
#include "websocketprotocol.h"
#include "websocketstates.h"
#include <iostream>

using namespace std;

/**
 * @brief websocketimpl::websocketimpl
 *      initialize websocket decoder
 */
websocketimpl::websocketimpl()
{
    initWebsocket();
}

/**
 * @brief websocketimpl::initWebsocket
 *     called at each initial state of the state machine
 */
void websocketimpl::initWebsocket()
{
    currentState = NONE;
    sizeCounter = 0;
    message = WebSocketMessage();
    payloadLengthCounter = 0;
    maskKeyCounter = 0;
    opened=true;
}

/**
 * @brief websocketimpl::setOpen
 *      set websocket opening state
 * @param open
 */
void websocketimpl::setOpen(bool open)
{
    opened=open;
}

/**
 * @brief websocketimpl::isOpen
 *      to know if websocket is openned or not
 * @return
 */
bool websocketimpl::isOpen()
{
    return opened;
}

/**
 * @brief websocketimpl::getCurrentState
 *      retrieve current state of the state machine
 * @return
 */
int websocketimpl::getCurrentState()
{
    return currentState;
}

/**
 * @brief websocketimpl::setDebug
 *      set debug state for websocket decoder
 * @param debugArg
 *      debug state
 */
void websocketimpl::setDebug(bool debugArg)
{
    debug=debugArg;
}

/**
 * @brief websocketimpl::websocketParse
 *      Websocket decoder state machine
 *
 * @param socket
 *      websocket from which streaming is decoded
 * @return
 */
QList<string> websocketimpl:: websocketParse(QTcpSocket* socket){

    QList<string> messageList;

    int currentByte = -2;
    char ch =0;

    while ((currentByte=socket->read(&ch,sizeof(ch)))!=0)
    {
        int data = ((int) ch & 0xFF);

        switch (currentState) {
            case NONE:
            {
                sizeCounter = 0;
                currentState = FIN_STATE;
            }
            case FIN_STATE:
            {
                message.setFIN(data & WEBSOCKET_PROTOCOL_FIN);
                currentState = RSV_STATE;
            }
            case RSV_STATE:
            {
                message.setRSV(data & WEBSOCKET_PROTOCOL_RSV);
                currentState = OPCODE_STATE;
            }
            case OPCODE_STATE:
            {
                message.setOPCODE(data & WEBSOCKET_PROTOCOL_OPCODE);
                message.setOpcodeType(data & WEBSOCKET_PROTOCOL_OPCODE);

                if (message.getOpcodeType() == CONNECTION_CLOSE_FRAME) {
                    if (debug)
                        cout << "websocket closing event received !" << endl;

                    initWebsocket();
                    opened=false;
                    return messageList;
                } else {
                    /* print opcode type */
                }
                currentState = MASK_STATE;
                break;
            }
            case MASK_STATE:
            {
                message.setMASK(data & WEBSOCKET_PROTOCOL_MASK);
                currentState = PAYLOAD_LENGTH;
            }
            case PAYLOAD_LENGTH:
            {
                message.setPAYLOAD_LENGTH_FRAME(data
                        & WEBSOCKET_PROTOCOL_PAYLOAD_LENGTH);
                if (message.getPAYLOAD_LENGTH_FRAME() < WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT1) {
                    message.setPayload_length(message
                            .getPAYLOAD_LENGTH_FRAME());
                    if (message.getMASK() == 0x01) {
                        currentState = MASKING_KEY;
                        message.maskKey = QByteArray(WEBSOCKET_PROTOCOL_MASK_KEY_SIZE,0);
                    } else {
                        message.payloadData = QByteArray(message
                                .getPayload_length(),0);
                        currentState = PAYLOAD_DATA;
                    }
                } else if (message.getPAYLOAD_LENGTH_FRAME() == WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_LIMIT1) {
                    message.payloadLength = QByteArray(WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_2BYTES,0);
                    currentState = PAYLOAD_LENGTH_2_BYTES;
                } else {
                    message.payloadLength = QByteArray(WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_8BYTES,0);
                    currentState = PAYLOAD_LENGTH_8_BYTES;
                }
                break;
            }
            case PAYLOAD_LENGTH_2_BYTES:
            {
                message.payloadLength[sizeCounter] =data;
                sizeCounter++;
                if (sizeCounter == WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_2BYTES) {
                    message.setPayload_length(message.payloadLength);
                    if (message.getMASK() == 0x01) {
                        currentState = MASKING_KEY;
                        message.maskKey = QByteArray(WEBSOCKET_PROTOCOL_MASK_KEY_SIZE,0);
                    } else {
                        message.payloadData = QByteArray(message
                                .getPayload_length(),0);
                        currentState = PAYLOAD_DATA;
                    }
                }
                break;
            }
            case PAYLOAD_LENGTH_8_BYTES:
            {
                message.payloadLength[sizeCounter] = data;
                sizeCounter++;
                if (sizeCounter == WEBSOCKET_PROTOCOL_PAYLOAD_SIZE_8BYTES) {
                    message.setPayload_length(message.payloadLength);
                    if (message.getMASK() == 0x01) {
                        currentState = MASKING_KEY;
                        message.maskKey = QByteArray(WEBSOCKET_PROTOCOL_MASK_KEY_SIZE,0);
                    } else {
                        message.payloadData = QByteArray(message
                                .getPayload_length(),0);
                        currentState = PAYLOAD_DATA;
                    }
                }
                break;
            }
            case MASKING_KEY:
            {
                message.maskKey[maskKeyCounter] =  data;
                maskKeyCounter++;
                if (maskKeyCounter == WEBSOCKET_PROTOCOL_MASK_KEY_SIZE) {
                    message.payloadData = QByteArray(message
                            .getPayload_length(),0);
                    currentState = PAYLOAD_DATA;
                }
                break;
            }
            case PAYLOAD_DATA:
            {
                message.payloadData[payloadLengthCounter] =  data;
                payloadLengthCounter++;
                if (payloadLengthCounter == message.getPayload_length()) {
                    currentState = FINISHED_LOADING;
                } else {
                    break;
                }
            }
            case FINISHED_LOADING:
            {
                string data = "";

                if (message.getMASK() == 0x01) {
                    data = QString(unmask(message.payloadData,
                            message.maskKey)).toStdString();
                } else {
                    data = QString(message.payloadData).toStdString();
                }
                initWebsocket();

                messageList.push_back(data);
            }
        }
    }

    return messageList;
}

/**
 * Unmask data payload according to algorithm described in websocket
 * protocol rfc <br/>
 * <br/>
 * Octet i of the transformed data ("transformed-octet-i") is the XOR of
 * octet i of the original data ("original-octet-i") with octet at index i
 * modulo 4 of the masking key ("masking-key-octet-j"):
 *
 * j = i MOD 4 transformed-octet-i = original-octet-i XOR
 * masking-key-octet-j
 *
 * @param maskedData
 *            data masked (from client)
 * @param mask
 *            mask id byte array
 * @return unmasked data payload
 */
QByteArray websocketimpl::unmask(QByteArray maskedData, QByteArray mask) {
    QByteArray unmaskedData(maskedData.length(),0);
    for (int i = 0; i < maskedData.length(); i++) {
        unmaskedData[i] = (((maskedData[i] & 0xFF) ^ (mask[i % 4] & 0xFF)) & 0xFF);
    }
    return unmaskedData;
}
