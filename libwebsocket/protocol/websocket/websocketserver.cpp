/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Bertrand Martel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "websocketserver.h"
#include "iostream"
#include "protocol/inter/http/httpconsumer.h"
#include "string"
#include "websockethandshake.h"
#include "clientsocketobj.h"
#include "utils/stringutils.h"

using namespace std;

/**
 * @brief WebsocketServer::socketClientList
 *      static list featuring all socket client connected to server
 */
std::map<QTcpSocket*,ClientSocketObj > WebsocketServer::socketClientList;

/**
 * @brief WebsocketServer::WebsocketServer
 *      construct for websocket server init new connection signal and set consumer
 *
 * @param parent
 */
WebsocketServer::WebsocketServer(QObject* parent): QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(handleNewConnection()));
    consumer=new httpconsumer;
    debug=true;

    //secure socket is disable for default config
    ssl=false;
}

/**
 * @brief WebsocketServer::handleNewConnection
 *      a new connection has come to server
 */
void WebsocketServer::handleNewConnection()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());

    if (debug)
        qDebug() << "New connection detected..." << endl;

    clientSocket = this->nextPendingConnection();
    if (!clientSocket) {
        qWarning("ERROR => not enough memory to create new QSslSocket");
        return;
    }

    // connect signals to slot
    connectSocketSignals(clientSocket);

    // only for ssl encryption
    if (ssl)
        startServerEncryption((QSslSocket*) clientSocket);
}

/**
 * @brief WebsocketServer::connectSocketSignals
 *      connect signals to slots : we take the maximum of slots here to manage errors quickly
 * @param clientSocket
 *      client socket incoming
 */
void WebsocketServer::connectSocketSignals (QTcpSocket* clientSocket)
{
    //slots for ssl cert handshake process and error monitoring
    if (ssl)
    {
        connect(clientSocket, SIGNAL(encrypted())                        ,this, SLOT(slot_encrypted()));
        connect(clientSocket, SIGNAL(encryptedBytesWritten(qint64))      ,this, SLOT(slot_encryptedBytesWritten(qint64)));
        connect(clientSocket, SIGNAL(modeChanged(QSslSocket::SslMode))   ,this, SLOT(slot_modeChanged(QSslSocket::SslMode)));
        connect(clientSocket, SIGNAL(peerVerifyError(const QSslError &)) ,this, SLOT(slot_peerVerifyError (const QSslError &)));
        connect(clientSocket, SIGNAL(sslErrors(const QList<QSslError> &)),this, SLOT(slot_sslErrors(const QList<QSslError> &)));
    }

    //slots for all socket types
    connect(clientSocket, SIGNAL(readyRead())                        ,this, SLOT(incomingData()));
    connect(clientSocket, SIGNAL(connected())                        ,this, SLOT(slot_connected()));
    connect(clientSocket, SIGNAL(disconnected())                     ,this, SLOT(slot_disconnected()));
    connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slot_error(QAbstractSocket::SocketError)));
    connect(clientSocket, SIGNAL(hostFound())                        ,this, SLOT(slot_hostFound()));
    connect(clientSocket, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)),this, SLOT(slot_proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(slot_stateChanged(QAbstractSocket::SocketState)));
}

/**
 * @brief WebsocketServer::startServerEncryption
 *      add respective certificates for SSL encryption
 *
 * @param clientSocket
 *      ssl client socket
 */
void WebsocketServer::startServerEncryption (QSslSocket* clientSocket)
{
    if (debug)
        cout << "server encryption" << endl;

    if (debug)
        qDebug("setting private key...");
    clientSocket->setPrivateKey(keyCertificate);

    if (debug)
        qDebug("setting local certificate...");

    clientSocket->setLocalCertificate(localCertificate);

    if (debug)
        qDebug("adding ca certificates...");

    clientSocket->addCaCertificates(caCertificate);

    clientSocket->setProtocol(QSsl::AnyProtocol);

    if (debug)
        qDebug("starting server encryption...");

    clientSocket->startServerEncryption();

}

/**
 * @brief WebsocketServer::slot_disconnected
 *      slot used when one client socket disconnect form websocket server
 */
void WebsocketServer::slot_disconnected()
{
    if (debug)
        qDebug() <<  "slot_disconnected() : Socket disconnected..." << endl;

    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (!client)
        return;

    //remove client socket from list
    socketClientList.erase(client);

    //safe delete
    client->deleteLater();
}

void WebsocketServer::ready()
{
}

void WebsocketServer::slot_encryptedBytesWritten (qint64 written)
{
    if (debug)
        qDebug("QMyServer::slot_encryptedBytesWritten(%ld)", (long) written);
}

void WebsocketServer::slot_modeChanged (QSslSocket::SslMode mode)
{
    if (debug)
        qDebug("QMyServer::slot_modeChanged(%d)", mode);
}

void WebsocketServer::slot_peerVerifyError (const QSslError &)
{
    if (debug)
        qDebug("QMyServer::slot_peerVerifyError");
}

void WebsocketServer::slot_sslErrors (const QList<QSslError> &)
{
    if (debug)
        qDebug("QMyServer::slot_sslErrors");
}

void WebsocketServer::slot_encrypted()
{
    if (debug)
        qDebug("QMyServer::slot_encrypted");
}
void WebsocketServer::slot_connected ()
{
    if (debug)
        qDebug("QMyServer::slot_connected");
}

void WebsocketServer::slot_error (QAbstractSocket::SocketError err)
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    if (debug)
        cout << "received error !" << endl;

    if (debug)
        qDebug() << __PRETTY_FUNCTION__ << err << client->errorString();
}

void WebsocketServer::slot_hostFound ()
{
    if (debug)
        qDebug("QMyServer::slot_hostFound");
}

void WebsocketServer::slot_proxyAuthenticationRequired (const QNetworkProxy &, QAuthenticator *)
{
    if (debug)
        qDebug("QMyServer::slot_proxyAuthenticationRequired");
}

void WebsocketServer::slot_stateChanged (QAbstractSocket::SocketState state)
{
    if (debug)
        qDebug() << "QMyServer::slot_stateChanged(" << state << ")";
}

/**
 * @brief WebsocketServer::~WebsocketServer
 *      desctruct => delete pointers
 */
WebsocketServer::~WebsocketServer()
{
  delete consumer;
  consumer=0;
}

/**
 * @brief WebsocketServer::incomingData
 *      that slot is for data coming from client socket
 */
void WebsocketServer::incomingData()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());

    //we manage socket client object from static list (thats where we store client)
    ClientSocketObj obj =WebsocketServer::socketClientList[clientSocket];

    //set socket as open (it doesnt mean that websocket is open only the socket)
    obj.setOpen(true);

    // check if websocket protocol has already been upgraded (websocket data input)
    if (obj.isWebsocketData())
    {
        //parse websocket streaming data
        QList<string>action = obj.websocketParse(clientSocket);

        //check if websocket is still open
        if (!obj.isOpen())
        {
            //close socket => it will be completly closed when slot_disconnected signal will be called
            closeClientSocket(clientSocket);
        }
        else
        {
            //manage messages
            for (int i = 0 ; i< action.size();i++)
                cout << "message n°"<< i << " received : " << action.at(i).data() << endl;

            WebSocketMessage response= WebSocketMessage("Hello I'm websocket server !");
            clientSocket->write(response.buildMessage());
            clientSocket->flush();
        }
    }
    else
    {
        QByteArray data = clientSocket->readAll();

        //http streaming data is decoded here
        decoder.httpdecode(consumer,&data);

        if (consumer->getHttpFrameList().size()>0)
        {
            int count = consumer->getHttpFrameList().size()-1;

            //iterate through all http streaming frames
            while (consumer->getHttpFrameList().size()>0)
            {
                //take into account only http frames that have been processed successfully
                if (consumer->getHttpFrameList().at(count)->isFinishedProcessing())
                {
                    //check that websocket handshake from client has been detected
                    if (websockethandshake::getWebsocketHandshakeProcess(consumer->getHttpFrameList().at(count)->getHeaders()))
                    {
                        //write websocket handshake to client
                        QTextStream os(clientSocket);
                        os.setAutoDetectUnicode(true);

                        os << websockethandshake::buildWebsocketHandshake(stringutils::trim((*consumer->getHttpFrameList().at(count)->getHeaders()).at("Sec-WebSocket-Key")).data()).data();
                        os.flush();

                        obj.setWebsocketState(true);
                    }

                    //last element of http frame must be removed to avoid to be popped next time we process frames
                    std::vector<Ihttpframe*> frameList = consumer->getHttpFrameList();
                    frameList.pop_back();
                    consumer->setHttpFrameList(&frameList);
                }
                else
                    cout << "Current HTTP frame has not been processed correctly." << endl;

                count--;
            }
        }

        //client socket must be closed if websocket protocol has not been upgraded
        if (!obj.isWebsocketData())
        {
            closeClientSocket(clientSocket);
        }
    }

    // we store pointer to client socket to be reused at any time
    socketClientList[clientSocket]= obj;
}

/**
 * @brief WebsocketServer::closeClientSocket
 *      close client socket function
 * @param socket
 *      client socket
 */
void WebsocketServer::closeClientSocket(QTcpSocket* socket)
{
    cout << "closing socket..." << endl;

    if (socket->isOpen())
        socket->close();

    //manage unconnected state
    if (socket->state() == QTcpSocket::UnconnectedState) {
         delete socket;
         cout << "Connection closed" << endl;
    }
}
