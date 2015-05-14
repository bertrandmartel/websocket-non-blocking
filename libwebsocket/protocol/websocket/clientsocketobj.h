#ifndef CLIENTSOCKETOBJ_H
#define CLIENTSOCKETOBJ_H

#include <QByteArray>
#include <QTcpSocket>
#include <QList>
#include "websocketimpl.h"

class ClientSocketObj
{

public:

    /**
     * @brief ClientSocketObj::ClientSocketObj
     *      Build one client
     */
    ClientSocketObj();

    /**
     * @brief ClientSocketObj::websocketParse
     *      decode websocket data from socket
     * @param socket
     *      client socket
     * @return
     *      list of string message decoded from websocket
     */
    QList<std::string> websocketParse(QTcpSocket* socket);

    /**
     * @brief ClientSocketObj::setOpen
     *      set opening state for websocket
     * @param open
     *      opening state
     */
    void setOpen(bool open);

    /**
     * @brief ClientSocketObj::isOpen
     *      determine if websocket connection is ON
     * @return
     */
    bool isOpen();

    /**
     * @brief ClientSocketObj::setWebsocketState
     *      set ENABLING state of websocket => mean socket connection will be maintained from that moment if state==true
     * @param state
     */
    void setWebsocketState(bool state);

    /**
     * @brief ClientSocketObj::isWebsocketData
     *      retrieve websocket ENABLING state
     * @return
     *      state
     */
    bool isWebsocketData();

private:

    /**
     * @brief websocketState
     *      define websocket ENABLING state
     */
    bool websocketState;

    /**
     * @brief websocketData
     *      websocket decoder object
     */
    websocketimpl websocketData;
};

#endif // CLIENTSOCKETOBJ_H
