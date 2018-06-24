#include "websocketcontroller.h"
#include "../src_websocket/websocketserver.h"
#include <QWebChannel>
#include <QWebSocketServer>
#include "../src_wrappers/websocketclientwrapper.h"
#include "../src_websocket/websockettransport.h"
#include "../src_interfaces/clientinteraction.h"
#include "../src_websocket/websocketclient.h"
#include "../src_interfaces/databasecontroller.h"
#include "../src_interfaces/firewallcontroller.h"
#include "../src_interfaces/configcontroller.h"
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QCoreApplication>
#include <QDir>
#include <QSettings>
WebSocketController::WebSocketController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{

    m_settings = new ConfigController(this);
    bool enable_ssl = m_settings->settings()->value("enable_ssl", "false").toBool();

    if (!enable_ssl) {
        server = new QWebSocketServer(QStringLiteral("WP Daemon Websocket Listener"), QWebSocketServer::NonSecureMode, this);
    } else {
        qDebug() << "Running in Secure Mode";
     server = new QWebSocketServer(QStringLiteral("WP Daemon Websocket Listener"), QWebSocketServer::SecureMode, this);


    QSslConfiguration sslConfiguration;
  /*    QFile certFile(QStringLiteral(":/localhost.cert"));
QFile keyFile(QStringLiteral(":/localhost.key")); */


    QFile certFile(m_settings->settings()->value("ssl_certificate_file", qApp->applicationDirPath().append(QDir::separator()).append(QStringLiteral("fullchain.cert"))).toString());
    QFile keyFile(m_settings->settings()->value("ssl_key_file", qApp->applicationDirPath().append(QDir::separator()).append(QStringLiteral("fullchain.key"))).toString());
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
    server->setMaxPendingConnections(3);
    server->setSslConfiguration(sslConfiguration);
 }
    if (!server->listen(QHostAddress::LocalHost, 65300)) {
        qFatal("Failed to open web socket server.");
        //return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    clientWrapper = new WebSocketClientWrapper(server);

    QObject::connect(clientWrapper, &WebSocketClientWrapper::clientConnected,
                     this, &WebSocketController::newClient);

    m_firewall = new FirewallController(this, this->m_db);

}

void WebSocketController::newClient(WebSocketTransport *client)
{
    new_client = new  WebSocketClient(this, client, m_db, this->m_firewall);
}
