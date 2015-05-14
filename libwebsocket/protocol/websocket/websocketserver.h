/**
    websocketserver.h

    Websocket server main process class

    manage incoming connections
    manage socket encryption for SSL socket
    manage process of incoming data from client socket

    @author Bertrand Martel
    @version 1.0
*/
#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include "libwebsocket_global.h"
#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSslSocket>
#include "protocol/inter/http/httpconsumer.h"
#include "protocol/http/httpdecoder.h"
#include "clientSocket.h"
#include "QSslCertificate"
#include "QList"
#include "QSslKey"
#include "IClientEventListener.h"

/**
 * @brief The WebsocketServer class
 *      Websocket server main process class
 *
 * <ul>
 *  <li>manage incoming connections</li>
 *  <li>manage socket encryption for SSL socket</li>
 *  <li>manage process of incoming data from client socket</li>
 * </ul>
 */
class LIBWEBSOCKETSHARED_EXPORT WebsocketServer: public QTcpServer
{

    Q_OBJECT

public:

    /**
     * @brief WebsocketServer
     *      websocket server build object
     * @param parent
     */
    WebsocketServer(QObject * parent = 0);

    /**
    * @brief socketClientList
    *        socket client list
    */
    static std::map<QTcpSocket*,ClientSocket > socketClientList;

    ~WebsocketServer();

    /**
    * @brief WebsocketServer::addClientEventListener
    *      add a client event listener to list
    * @param clientListener
    *      client listener
    */
    void addClientEventListener(IClientEventListener * clientListener);

private slots:

    /**
     * @brief incomingData
     *      slot called when data comes from client socket
     */
    void incomingData();

    /**
     * @brief handleNewConnection
     *      called when a new connection pop up
     */
    void handleNewConnection();

    /**
     * @brief slot_connected
     *      called when a socket connect successfully to server
     */
    void slot_connected ();

    /**
     * @brief slot_disconnected
     *      called when a socket disconnect from server
     */
    void slot_disconnected ();

    void ready();

    void slot_error (QAbstractSocket::SocketError err);
    void slot_hostFound ();
    void slot_proxyAuthenticationRequired (const QNetworkProxy &, QAuthenticator *);
    void slot_stateChanged (QAbstractSocket::SocketState state);

    //bunch of slots used to check different state of SSL encryption process through QTNetwork processing
    void slot_encrypted ();
    void slot_encryptedBytesWritten (qint64 written);
    void slot_modeChanged (QSslSocket::SslMode mode);
    void slot_peerVerifyError (const QSslError &);
    void slot_sslErrors (const QList<QSslError> &);

private:

    /**
     * @brief WebsocketServer::startServerEncryption
     *      add respective certificates for SSL encryption
     *
     * @param clientSocket
     *      ssl client socket
     */
    void startServerEncryption(QSslSocket* clientSocket);

    /**
     * @brief WebsocketServer::connectSocketSignals
     *      connect signals to slots : we take the maximum of slots here to manage errors quickly
     * @param clientSocket
     *      client socket incoming
     */
    void connectSocketSignals(QTcpSocket* clientSocket);

    /**
     * @brief WebsocketServer::closeClientSocket
     *      close client socket function
     * @param socket
     *      client socket
     */
    void closeClientSocket(QTcpSocket* socket);

    //ssl certs used to encrypt ssl socket
    QSslCertificate localCertificate;
    QList< QSslCertificate > caCertificate;
    QSslKey keyCertificate;

    /**
     * @brief consumer
     *      http consumer used to retrieve chunk of http frames
     */
    httpconsumer * consumer;

    /**
     * @brief decoder
     *          http decoder used to decode http frames streaming
     */
    httpdecoder decoder;

    /**
     * @brief debug
     *      debug state for websocket server
     */
    bool debug;

    /**
     * @brief ssl
     *      define if websocket protocol must use encryption or not
     */
    bool ssl;

    /**
     * @brief clientEventListenerList
     *      list of client event listener
     */
    std::vector<IClientEventListener*> clientEventListenerList;

};


#endif // WEBSOCKETSERVER_H
