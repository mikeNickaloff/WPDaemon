#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H

#include <QObject>

class LoginController;
class DatabaseController;
/* this is the controller that clients will talk to via webchannel */
class ClientInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ClientInteraction(QObject *parent = nullptr, LoginController *i_login = nullptr);
    LoginController* loginController;
    Q_INVOKABLE bool login_request(QString username, QString password);
signals:
    void requireLogin();
public slots:

};

#endif // CLIENTINTERACTION_H