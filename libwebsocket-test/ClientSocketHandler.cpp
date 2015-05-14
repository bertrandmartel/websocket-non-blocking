/**
    ClientSocketHandler.cpp
    Client socket managing event handler

    @author Bertrand Martel
    @version 1.0
*/
#include "ClientSockethandler.h"

#include "protocol/websocket/IWebsocketClient.h"
#include "iostream"
#include "string"

using namespace std;

ClientSocketHandler::ClientSocketHandler()
{

}

ClientSocketHandler::~ClientSocketHandler()
{

}

/**
 * called when a websocket client connection closes
 *
 * @param clientRef
 */
void ClientSocketHandler::onClientClose(IWebsocketClient &client)
{
    cout << "Client socket closed" << endl;
}

/**
 * called when a websocket client has successfully connected to server
 *
 * @param client
 */
void ClientSocketHandler::onClientConnection(IWebsocketClient &client)
{
    cout << "Client socket opened" << endl;
}

/**
 * called when a message has been received from client
 *
 * @param client
 * 		client object
 * @param message
 * 		message delivered
 */
void ClientSocketHandler::onMessageReceivedFromClient(IWebsocketClient &client,string message)
{
    cout << "Client socket message received : " << message.data() << endl;

    client.sendMessage("OK I received your message !");
}
