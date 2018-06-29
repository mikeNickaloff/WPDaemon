#ifndef CLIENTINTERACTION_H
#define CLIENTINTERACTION_H

#include <QObject>
#include <QVariant>
#include <QJsonDocument>
class LoginController;
class DatabaseController;
class FirewallController;
class Submodule;
class SubmoduleCommand;
class CommandParameter;
class ProcessLauncherThread;
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
    Q_INVOKABLE QVariant allowedSubmodules();
    Q_INVOKABLE QVariant set_current_submodule(QString i_module);
    Q_INVOKABLE QVariant set_current_command(QString i_command);
    Submodule* currentSubmodule;
    ProcessLauncherThread* processLauncher;
    Q_INVOKABLE QVariant execute();
signals:
    void requireLogin();
    void LoginSuccessful();
    void LoginFailed();
public slots:
    Q_INVOKABLE void set_parameter_value(int paramidx, QVariant val);

};

#endif // CLIENTINTERACTION_H