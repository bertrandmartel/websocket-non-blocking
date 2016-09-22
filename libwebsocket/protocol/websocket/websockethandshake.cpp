/**
    websockethandshake.cpp

    manage websocket handshake process

    @author Bertrand Martel
    @version 1.0
*/
#include "websockethandshake.h"
#include "string"
#include "crypto/sha1.h"
#include "crypto/base64.h"
#include <string.h>
#include "iostream"

using namespace std;

/**
 * @brief websockethandshake::buildWebsocketHandshake
 *      build handshake to be sent to socket client to establish websocket connection
 * @param websocketKey
 *      websocket key sent from client
 * @return
 *      websocket data handshake response to client
 */
string websockethandshake::buildWebsocketHandshake(std::string websocketKey){

    string globalUid = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    string websocketKeyToSend = websocketKey + globalUid;

    unsigned char hash[200];
    char hexstring[100];
    int length = sha1::calc(websocketKeyToSend.data(),websocketKeyToSend.length(),hash);
    sha1::toHexString(hash,hexstring);
    string encoded = base64::base64_encode(hash,length);

    string ret = "HTTP/1.0 101 Switching Protocols\r\nContent-Type: application/json; charset=utf-8\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: " + encoded + "\r\n\r\n";

    return ret.data();
}

/**
 * @brief websockethandshake::getWebsocketHandshakeProcess
 *      to know if the current http headers sent in parameter is containing or not a websocket handhsake request
 * @param headerMap
 *      http headers
 * @return
 */
bool websockethandshake::getWebsocketHandshakeProcess(std::map<std::string,std::string> headerMap){

    bool upgradeHeader = false;
    bool connectionHeader = false;
    bool websocketKeyHeader = false;

    for(std::map<std::string, std::string>::iterator it = headerMap.begin(); it != headerMap.end(); it++) {

        if (strcmp(it->first.c_str(),"Upgrade")==0 && strcmp(it->second.c_str(),"websocket")==0)
            upgradeHeader=true;
        if (strcmp(it->first.c_str(),"Connection")==0 && strcmp(it->second.c_str(),"Upgrade")==0)
            connectionHeader=true;
        if (strcmp(it->first.c_str(),"Sec-WebSocket-Key")==0)
            websocketKeyHeader=true;
    }

    if (upgradeHeader && connectionHeader && websocketKeyHeader)
        return true;
    else
        return false;
}
