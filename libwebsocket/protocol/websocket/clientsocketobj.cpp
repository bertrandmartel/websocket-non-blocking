#include "clientsocketobj.h"

#include <QTcpSocket>
#include <iostream>

using namespace std;

/**
 * @brief ClientSocketObj::ClientSocketObj
 *      Build one client
 */
ClientSocketObj::ClientSocketObj()
{
    websocketState=false;
}

/**
 * @brief ClientSocketObj::websocketParse
 *      decode websocket data from socket
 * @param socket
 *      client socket
 * @return
 *      list of string message decoded from websocket
 */
QList<string> ClientSocketObj::websocketParse(QTcpSocket* socket)
{
    return websocketData.websocketParse(socket);
}

/**
 * @brief ClientSocketObj::setOpen
 *      set opening state for websocket
 * @param open
 *      opening state
 */
void ClientSocketObj::setOpen(bool open)
{
    websocketData.setOpen(open);
}

/**
 * @brief ClientSocketObj::isOpen
 *      determine if websocket connection is ON
 * @return
 */
bool ClientSocketObj::isOpen()
{
    return websocketData.isOpen();
}

/**
 * @brief ClientSocketObj::setWebsocketState
 *      set ENABLING state of websocket => mean socket connection will be maintained from that moment if state==true
 * @param state
 */
void ClientSocketObj::setWebsocketState(bool state)
{
    websocketState=state;
}

/**
 * @brief ClientSocketObj::isWebsocketData
 *      retrieve websocket ENABLING state
 * @return
 *      state
 */
bool ClientSocketObj::isWebsocketData()
{
    return websocketState;
}
