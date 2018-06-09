#ifndef WEBSOCKETCONTROLLER_H
#define WEBSOCKETCONTROLLER_H

#include <QObject>

class WebSocketController : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WEBSOCKETCONTROLLER_H