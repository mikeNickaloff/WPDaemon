#include "websocketcontroller.h"
#include "../src_websocket/websocketserver.h"
#include <QWebChannel>
#include <QWebSocketServer>
#include "../src_wrappers/websocketclientwrapper.h"
#include "../src_websocket/websockettransport.h"
#include "../src_interfaces/clientinteraction.h"
#include "../src_websocket/websocketclient.h"
#include "../src_interfaces/databasecontroller.h"
WebSocketController::WebSocketController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
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
  //  channel = new QWebChannel(this);
    QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
                     this, &WebSocketController::newClient);


    // setup the dialog and publish it to the QWebChannel
//    ClientInteraction* clientGateway = new ClientInteraction(this);
//    channel->registerObject(QStringLiteral("ClientInteraction"), clientGateway);

}

void WebSocketController::newClient(WebSocketTransport *client)
{
    new_client = new  WebSocketClient(this, client, m_db);
}
