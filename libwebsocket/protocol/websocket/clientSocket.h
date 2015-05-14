/**
    clientsocket.h

    websocket client object featuring one physical websocket connection

    @author Bertrand Martel
    @version 1.0
*/
#ifndef CLIENTSOCKETOBJ_H
#define CLIENTSOCKETOBJ_H

#include <QByteArray>
#include <QTcpSocket>
#include <QList>
#include "websocketimpl.h"
#include "IWebsocketClient.h"

class ClientSocket : public IWebsocketClient
{

public:

    /**
     * @brief ClientSocketObj::ClientSocketObj
     *      Build one client
     */
    ClientSocket();


    ~ClientSocket();

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

    /**
     *  close websoclet client object
     *
     * @return
     * 		0 if success -1 if error
     */
    int close();

    /**
     * Send a message to websocket client
     *
     * @param string
     * 		Message to be sent to client
     * @return
     *		0 if success -1 if error
     */
    int sendMessage(std::string message);

    /**
     * @brief setSocketClient
     *      Define client socket for this object
     * @param clientSocket
     *      client socket
     */
    void setSocketClient(QTcpSocket * clientSocket);

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

    /**
     * @brief clientSocket
     *      client socket
     */
    QTcpSocket* clientSocket;
};

#endif // CLIENTSOCKETOBJ_H
