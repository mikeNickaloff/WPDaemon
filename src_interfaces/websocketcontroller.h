#ifndef WEBSOCKETCONTROLLER_H
#define WEBSOCKETCONTROLLER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebChannel>
#include "../src_wrappers/websocketclientwrapper.h"
#include "../src_websocket/websockettransport.h"

class WebSocketServer;
class ClientInteraction;
class LoginController;
class WebSocketClient;
class DatabaseController;
class WebSocketController : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketController(QObject *parent = nullptr, DatabaseController *i_db = nullptr);
    QWebSocketServer* server;
    QWebChannel* channel;
    WebSocketClientWrapper* clientWrapper;
    QHash<int, WebSocketClient*> clients;
    WebSocketClient* new_client;
    DatabaseController* m_db;
signals:

public slots:
    void newClient(WebSocketTransport *client);
};

#endif // WEBSOCKETCONTROLLER_H