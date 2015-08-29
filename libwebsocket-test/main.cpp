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
/**
    main.cpp

    Main test programm

    @author Bertrand Martel
    @version 1.0
*/
#include <QCoreApplication>
#include <protocol/websocket/websocketserver.h>
#include <iostream>
#include <QStringList>
#include <QDebug>
#include "string"
#include <sys/param.h>
#include "ClientSockethandler.h"
#include "SslHandler.h"

#define ROOT_FOLDER       "/home/abathur/Bureau/open_source"
#define PUBLIC_CERT       ROOT_FOLDER "/websocketcpp/libwebsocket-test/certs/server/server.crt"
#define PRIVATE_CERT      ROOT_FOLDER "/websocketcpp/libwebsocket-test/certs/server/server.key"
#define CA_CERTS          ROOT_FOLDER "/websocketcpp/libwebsocket-test/certs/ca.crt"
#define PRIVATE_CERT_PASS "12345"

using namespace std;

static int port = 8443;
static string ip="127.0.0.1";
static bool useSSL = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //ignore SIGPIPE signal (broken pipe issue)
    signal(SIGPIPE, SIG_IGN);

    QStringList args = a.arguments();

    string ip ="127.0.0.1";

    if (args.size() >2)
    {
        ip=args[1].toStdString();
        bool ok = false;
        int dec = args[2].toInt(&ok, 10);

        if (ok)
            port = dec;
    }

    ClientSocketHandler *clientHandler = new ClientSocketHandler();

    //instance of websocket server
    WebsocketServer server;

    if (useSSL)
    {
        //set secured websocket server
        server.setSSL(true);

        cout << "setting server certs ..." << endl;

        //set public / private and certification authority list into websocket server object
        server.setPublicCert(SslHandler::retrieveCertFromFile(PUBLIC_CERT));
        server.setPrivateCert(SslHandler::retrieveKeyCertFile(PRIVATE_CERT,PRIVATE_CERT_PASS));
        server.setCaCert(SslHandler::retrieveveCaCertListFromFile(CA_CERTS));
    }

    server.addClientEventListener(clientHandler);

    if (!server.listen(QHostAddress(ip.data()),port)) {
        qDebug() << "An error occured while initializing hope proxy server... Maybe another instance is already running on "<< ip.data() << ":" << port << endl;
        return -1;
    }

    cout << "Starting Websocket server on " <<  ip << ":" << port << endl;

    return a.exec();
}
