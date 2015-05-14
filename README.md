# Websocket non-blocking Server implementation in C++ #

http://akinaru.github.io/websocket-non-blocking-cpp/

<i>Last update 14/05/2015</i>

Websocket non-blocking Server implementation using QTNetwork framework (QT4)

You will find source in ./libwebsocket folder

* Very easy to use
* A sample is provided to launch a Websocket server and test with a Javascript Client in exemples/js folder

<hr/>

<b>How to launch Websocket Server ?</b>

```
WebsocketServer server;

bool success = server.listen(QHostAddress(ip),port)
```

Specifying your own ip / port

<hr/>

<b>How to monitor my clients connected to server ?</b>

Just add a Listener to server object. You have 3 callbacks that will notify you on client connection change and arrival of client messages

TODO : add an exemple

<hr/>

<b>How to close my websocket server ?</b>

``server.close();``

<hr/>

<b>COMMAND LINE SYNTAX</b> 

From /libwesocket-test/release folder : 

The following will open a websocket on port 4242 (default port value for my exemple)

``./libwebsocket-test 127.0.0.1 4343``

You can add library path to LD_LIBRARY_PATH variable for a quick run :

``LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ROOT/websocket-non-blocking-cpp/lib/:$ROOT/websocket-non-blocking-cpp/libwebsocket/release/``

<hr/>

<b>Exemple with Javascript Client</b>

* Launch the websocket server on port 4242
* Open the javascript client page in ./exemples/js/ folder

=> You have now a complete websocket chat between C++ websocket server <-> javascript client in websocket 

![alt tag](https://raw.github.com/akinaru/websocket-java/master/exemples/readme_images/clientSide.png)


![alt tag](https://raw.github.com/akinaru/websocket-java/master/exemples/readme_images/serverSide.png)
<hr/>

* Project is Qt4 compliant
* You can build it with qmake
* Development on QtCreator
* Specification from https://tools.ietf.org/html/rfc6455
