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
class WebsiteController;
/* this is the controller that clients will talk to via webchannel */
class ClientInteraction : public QObject
{
    Q_OBJECT
public:
    explicit ClientInteraction(QObject *parent = nullptr, LoginController *i_login = nullptr, FirewallController* i_firewall = nullptr, DatabaseController* i_db = nullptr);
    LoginController* loginController;
    FirewallController* firewallController;
    DatabaseController* db;
    Q_INVOKABLE bool login(QString username, QString password);
    Q_INVOKABLE bool tokenLogin(QString token);
    Q_INVOKABLE QVariant request_token();
    QString remoteIP;
    Q_INVOKABLE QVariant allowedSubmodules();
    Q_INVOKABLE QVariant set_current_submodule(QString i_module);
    Q_INVOKABLE QVariant set_current_command(QString i_command);
    Submodule* currentSubmodule;
    ProcessLauncherThread* processLauncher;
    Q_INVOKABLE QVariant execute();
    Q_INVOKABLE QVariant add_site(QString i_name, QString i_path);
    WebsiteController* websiteController;
    Q_INVOKABLE QVariant websites();
    Q_INVOKABLE bool set_current_site(QString sitename);
signals:
    void requireLogin();
    void LoginSuccessful();
    void LoginFailed();
public slots:
    Q_INVOKABLE void set_parameter_value(int paramidx, QVariant val);

};

#endif // CLIENTINTERACTION_H
