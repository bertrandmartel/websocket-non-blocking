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
#include "clientsocketobj.h"
#include "QSslCertificate"
#include "QList"
#include "QSslKey"

class LIBWEBSOCKETSHARED_EXPORT WebsocketServer: public QTcpServer
{
    Q_OBJECT
    public:

      WebsocketServer(QObject * parent = 0);

      explicit WebsocketServer(int port);

      static std::map<QTcpSocket*,ClientSocketObj > socketClientList;

      ~WebsocketServer();

    private slots:
        void incomingData();
        void handleNewConnection();
        void ready();

        void slot_encrypted ();
        void slot_encryptedBytesWritten (qint64 written);
        void slot_modeChanged (QSslSocket::SslMode mode);
        void slot_peerVerifyError (const QSslError &);
        void slot_sslErrors (const QList<QSslError> &);
        void slot_connected ();
        void slot_disconnected ();
        void slot_error (QAbstractSocket::SocketError err);
        void slot_hostFound ();
        void slot_proxyAuthenticationRequired (const QNetworkProxy &, QAuthenticator *);
        void slot_stateChanged (QAbstractSocket::SocketState state);

    private:

        void startServerEncryption(QSslSocket* clientSocket);

        void connectSocketSignals(QTcpSocket* clientSocket);

        void closeClientSocket(QTcpSocket* socket);

        //ssl certs used to encrypt ssl socket
        QSslCertificate localCertificate;
        QList< QSslCertificate > caCertificate;
        QSslKey keyCertificate;

        httpconsumer * consumer;

        httpdecoder decoder;

        bool debug;

        bool ssl;
};


#endif // WEBSOCKETSERVER_H
