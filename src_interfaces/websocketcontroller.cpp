#include "websocketcontroller.h"
#include "../src_websocket/websocketserver.h"
#include <QWebChannel>
#include <QWebSocketServer>
#include "../src_wrappers/websocketclientwrapper.h"
#include "../src_websocket/websockettransport.h"
#include "../src_interfaces/clientinteraction.h"
#include "../src_websocket/websocketclient.h"
#include "../src_interfaces/databasecontroller.h"
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QCoreApplication>
#include <QDir>
WebSocketController::WebSocketController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{

    server = new QWebSocketServer(QStringLiteral("WP Daemon Websocket Listener"), QWebSocketServer::NonSecureMode, this);


    QSslConfiguration sslConfiguration;
    /*  QFile certFile(QStringLiteral(":/localhost.cert"));
QFile keyFile(QStringLiteral(":/localhost.key"));

*/
    QFile certFile(qApp->applicationDirPath().append(QDir::separator()).append(QStringLiteral("fullchain.cert")));
    QFile keyFile(qApp->applicationDirPath().append(QDir::separator()).append(QStringLiteral("fullchain.key")));
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();
    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    sslConfiguration.setProtocol(QSsl::TlsV1SslV3);
    server->setSslConfiguration(sslConfiguration);

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
