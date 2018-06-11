#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebChannel>
#include <QWebChannelAbstractTransport>
class WebSocketTransport;
class ClientInteraction;
class LoginController;
class DatabaseController;
class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = nullptr, WebSocketTransport *client = nullptr, DatabaseController* i_db = nullptr);
      ClientInteraction* clientGateway;
    QWebChannel* channel;
    WebSocketTransport* m_transport;
    DatabaseController* m_db;
    LoginController* m_login;
signals:

public slots:

};

#endif // WEBSOCKETCLIENT_H