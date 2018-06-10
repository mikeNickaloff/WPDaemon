#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H

#include <QObject>

class LoginController;

/* this is the controller that clients will talk to via webchannel */
class ClientInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ClientInteraction(QObject *parent = nullptr);
    LoginController* loginController;
signals:

public slots:
    Q_INVOKABLE void login_request(QString username, QString password);
};

#endif // CLIENTINTERACTION_H