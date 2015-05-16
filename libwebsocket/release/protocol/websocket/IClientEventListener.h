/**
    IClientEventListener.h

    Define all client socket event that can happen and that will pop event in class that will inherit this one

    @author Bertrand Martel
    @version 1.0
*/
#ifndef ICLIENTEVENTLISTENER_H
#define ICLIENTEVENTLISTENER_H

#include "IWebsocketClient.h"
#include "string"

/**
 * @brief The IClientEventListener class
 *      Client Socket event listener template class
 */
class IClientEventListener
{

public :
    /**
     * called when a websocket client connection closes
     *
     * @param clientRef
     */
    virtual void onClientClose(IWebsocketClient &client)= 0;

    /**
     * called when a websocket client has successfully connected to server
     *
     * @param client
     */
    virtual void onClientConnection(IWebsocketClient &client)= 0;

    /**
     * called when a message has been received from client
     *
     * @param client
     * 		client object
     * @param message
     * 		message delivered
     */
    virtual void onMessageReceivedFromClient(IWebsocketClient &client,std::string message)= 0;
};


#endif // ICLIENTEVENTLISTENER_H
