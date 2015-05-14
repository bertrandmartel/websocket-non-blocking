/**
    websockethandshake.h

    manage websocket handshake process

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETHANDSHAKE_H
#define WEBSOCKETHANDSHAKE_H

#include "string"
#include "map"

#define WEBSOCKET_HANDSHAKE_CONNECTION "Connection"

#define WEBSOCKET_HANDSHAKE_UPGRADE "Upgrade"

#define WEBSOCKET_HANDSHAKE_UPGRADE_WEBSOCKET "websocket"

/**
 * @brief The websockethandshake class
 *      manage websocket handshake process
 */
class websockethandshake
{
    public:

    /**
     * @brief websockethandshake::buildWebsocketHandshake
     *      build handshake to be sent to socket client to establish websocket connection
     * @param websocketKey
     *      websocket key sent from client
     * @return
     *      websocket data handshake response to client
     */
    static std::string buildWebsocketHandshake(std::string websocketKey);

    /**
     * @brief websockethandshake::getWebsocketHandshakeProcess
     *      to know if the current http headers sent in parameter is containing or not a websocket handhsake request
     * @param headerMap
     *      http headers
     * @return
     */
    static bool getWebsocketHandshakeProcess(std::map<std::string,std::string> *headerMap);

};

#endif // WEBSOCKETHANDSHAKE_H
