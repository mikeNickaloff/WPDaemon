#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H

#include <QObject>

class LoginController;
class DatabaseController;
class FirewallController;
/* this is the controller that clients will talk to via webchannel */
class ClientInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ClientInteraction(QObject *parent = nullptr, LoginController *i_login = nullptr, FirewallController* i_firewall = nullptr);
    LoginController* loginController;
    FirewallController* firewallController;
    Q_INVOKABLE bool login(QString username, QString password);
    QString remoteIP;
signals:
    void requireLogin();
    void LoginSuccessful();
    void LoginFailed();
public slots:

};

#endif // CLIENTINTERACTION_H