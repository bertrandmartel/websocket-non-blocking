/**
    clientsocket.cpp

    websocket client object featuring one physical websocket connection

    @author Bertrand Martel
    @version 1.0
*/
#include "clientSocket.h"

#include <QTcpSocket>
#include <iostream>
#include "websocketmessage.h"

using namespace std;

/**
 * @brief ClientSocketObj::ClientSocketObj
 *      Build one client
 */
ClientSocket::ClientSocket()
{
    websocketState=false;
    clientSocket=0;
}

/**
 * @brief ClientSocket::~ClientSocket
 *      clean pointers
 */
ClientSocket::~ClientSocket()
{
    //client socket should NOT be deleted here => connection MUST be deleted in websocketserver class
}

/**
 * @brief ClientSocketObj::websocketParse
 *      decode websocket data from socket
 * @param socket
 *      client socket
 * @return
 *      list of string message decoded from websocket
 */
QList<string> ClientSocket::websocketParse(QTcpSocket* socket)
{
    return websocketData.websocketParse(socket);
}

/**
 * @brief ClientSocketObj::setOpen
 *      set opening state for websocket
 * @param open
 *      opening state
 */
void ClientSocket::setOpen(bool open)
{
    websocketData.setOpen(open);
}

/**
 * @brief ClientSocketObj::isOpen
 *      determine if websocket connection is ON
 * @return
 */
bool ClientSocket::isOpen()
{
    return websocketData.isOpen();
}

/**
 * @brief ClientSocketObj::setWebsocketState
 *      set ENABLING state of websocket => mean socket connection will be maintained from that moment if state==true
 * @param state
 */
void ClientSocket::setWebsocketState(bool state)
{
    websocketState=state;
}

/**
 * @brief ClientSocketObj::isWebsocketData
 *      retrieve websocket ENABLING state
 * @return
 *      state
 */
bool ClientSocket::isWebsocketData()
{
    return websocketState;
}

/**
 *  close websoclet client object
 *
 * @return
 * 		0 if success -1 if error
 */
int ClientSocket::close()
{
    clientSocket->close();

    return 0;
}

/**
 * Send a message to websocket client
 *
 * @param string
 * 		Message to be sent to client
 * @return
 *		0 if success -1 if error
 */
int ClientSocket::sendMessage(std::string message)
{
    WebSocketMessage response= WebSocketMessage(message.data());
    clientSocket->write(response.buildMessage());
    clientSocket->flush();

    return 0;
}

/**
 * @brief setSocketClient
 *      set socket client socket
 * @param clientSocket
 */
void ClientSocket::setSocketClient(QTcpSocket * clientSocket)
{
    this->clientSocket=clientSocket;
}
