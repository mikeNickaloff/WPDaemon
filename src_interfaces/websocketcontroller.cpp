#include "websocketcontroller.h"
#include "../src_websocket/websocketserver.h"
#include <QWebChannel>
#include <QWebSocketServer>
#include "../src_wrappers/websocketclientwrapper.h"
#include "../src_websocket/websockettransport.h"
#include "../src_interfaces/clientinteraction.h"
WebSocketController::WebSocketController(QObject *parent) : QObject(parent)
{
    server = new QWebSocketServer(QStringLiteral("WP Daemon Websocket Listener"),
                            QWebSocketServer::NonSecureMode);
    if (!server->listen(QHostAddress::LocalHost, 65300)) {
        qFatal("Failed to open web socket server.");
        //return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    clientWrapper = new WebSocketClientWrapper(server);

    // setup the channel
    channel = new QWebChannel(this);
    QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
                     channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    ClientInteraction* clientGateway = new ClientInteraction(this);
    channel->registerObject(QStringLiteral("ClientInteraction"), clientGateway);

}
