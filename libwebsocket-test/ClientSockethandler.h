/**
    ClientSocketHandler.h
    Client socket managing event handler

    @author Bertrand Martel
    @version 1.0
*/
#ifndef CLIENTSOCKETHANDLER_H
#define CLIENTSOCKETHANDLER_H
#include "protocol/websocket/IClientEventListener.h"

/**
 * @brief The ClientSocketHandler class
 *      Client socket managing event handler
 */
class ClientSocketHandler :  public IClientEventListener
{
    public:

         /**
         * @brief ClientSocketHandler
         *      build client socket handler
         */
        ClientSocketHandler();

        ~ClientSocketHandler();

        /**
         * called when a websocket client connection closes
         *
         * @param clientRef
         */
        void onClientClose(IWebsocketClient &client);

        /**
         * called when a websocket client has successfully connected to server
         *
         * @param client
         */
        void onClientConnection(IWebsocketClient &client);

        /**
         * called when a message has been received from client
         *
         * @param client
         * 		client object
         * @param message
         * 		message delivered
         */
        void onMessageReceivedFromClient(IWebsocketClient &client,std::string message);
};

#endif // CLIENTSOCKETHANDLER_H
