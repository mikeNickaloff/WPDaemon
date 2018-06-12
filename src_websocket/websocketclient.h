#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebChannel>
#include <QWebChannelAbstractTransport>
#include <QHostAddress>
class WebSocketTransport;
class ClientInteraction;
class LoginController;
class DatabaseController;
class FirewallController;
class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr, WebSocketTransport *i_client = nullptr, DatabaseController* i_db = nullptr, FirewallController* i_firewall = nullptr);
      ClientInteraction* clientGateway;
    QWebChannel* channel;
    WebSocketTransport* m_transport;
    WebSocketTransport* m_client;
    DatabaseController* m_db;
    LoginController* m_login;
    FirewallController* m_firewall;

    QHostAddress  remoteIP;
signals:

public slots:
void process_failed_login();
};

#endif // WEBSOCKETCLIENT_H