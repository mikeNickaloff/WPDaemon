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
class WebSocketController : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketController(QObject *parent = nullptr);
    QWebSocketServer* server;
    QWebChannel* channel;
    WebSocketClientWrapper* clientWrapper;
signals:

public slots:
};

#endif // WEBSOCKETCONTROLLER_H