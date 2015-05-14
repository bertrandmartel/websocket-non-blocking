#ifndef IWEBSOCKETCLIENT_H
#define IWEBSOCKETCLIENT_H
#include "string"

class IWebsocketClient
{

public :
    /**
     *  close websoclet client object
     *
     * @return
     * 		0 if success -1 if error
     */
    virtual int close()= 0;

    /**
     * Send a message to websocket client
     *
     * @param string
     * 		Message to be sent to client
     * @return
     *		0 if success -1 if error
     */
    virtual int sendMessage(std::string message)= 0;
};

#endif // IWEBSOCKETCLIENT_H
