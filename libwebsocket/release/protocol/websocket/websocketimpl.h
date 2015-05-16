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
/**
    websocketimpl.h

    Websocket protocol decoder

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETIMPL_H
#define WEBSOCKETIMPL_H

#include <QByteArray>
#include <QTcpSocket>
#include "websocketstates.h"
#include "websocketmessage.h"
#include <QList>

/**
 * @brief The websocketimpl class
 *      Websocket decoder
 */
class websocketimpl
{
public:

    /**
     * @brief websocketimpl::websocketimpl
     *      initialize websocket decoder
     */
    websocketimpl();

    bool webSocketHandShake(std::map<std::string,std::string> headers);

    /**
     * @brief websocketimpl::websocketParse
     *      Websocket decoder state machine
     *
     * @param socket
     *      websocket from which streaming is decoded
     * @return
     */
    QList<std::string> websocketParse(QTcpSocket* socket);

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
    QByteArray unmask(QByteArray maskedData,QByteArray mask);

    /**
     * @brief websocketimpl::initWebsocket
     *     called at each initial state of the state machine
     */
    void initWebsocket();

    /**
     * @brief websocketimpl::getCurrentState
     *      retrieve current state of the state machine
     * @return
     */
    int getCurrentState();

    /**
     * @brief websocketimpl::setDebug
     *      set debug state for websocket decoder
     * @param debugArg
     *      debug state
     */
    void setDebug(bool debug);

    /**
     * @brief websocketimpl::setOpen
     *      set websocket opening state
     * @param open
     */
    void setOpen(bool open);

    /**
     * @brief websocketimpl::isOpen
     *      to know if websocket is openned or not
     * @return
     */
    bool isOpen();

private:

    /**
     * @brief currentState
     *      current state of websocket state machine
     */
    int currentState;

    /**
     * @brief sizeCounter
     *      index for the size of the data payload
     */
    int sizeCounter;

    /**
     * @brief message
     *      websocket message object being decoded
     */
    WebSocketMessage message;

    /**
     * @brief payloadLengthCounter
     *      length of websocket data payload
     */
    int payloadLengthCounter;

    /**
     * @brief maskKeyCounter
     *      mask key length
     */
    int maskKeyCounter;

    /**
     * @brief debug
     *      debug state for websocket decoder
     */
    bool debug;

    /**
     * @brief opened
     *      determine of websocket connection is opened
     */
    bool opened;
};

#endif // WEBSOCKETIMPL_H
