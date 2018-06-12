#ifndef FIREWALLCONTROLLER_H
#define FIREWALLCONTROLLER_H

#include <QObject>
#include <QHostAddress>
#include <QDateTime>
#include <QString>

class DatabaseController;
class FirewallController : public QObject
{
    Q_OBJECT
public:
    explicit FirewallController(QObject *parent = nullptr, DatabaseController* i_db = nullptr);
    DatabaseController* m_db;
    QHash<int, QString> m_hosts;
    QHash<int, int> m_fails;
    QHash<int, qint64> m_times;
    QHash<QString, qint64> m_bans;
    bool isBanned(QString remoteIP);
    qint64 FAILED_LOGIN_BAN_TIME;
    qint64 FAILED_LOGIN_COUNT;
    qint64 FAILED_LOGIN_INTERVAL;
signals:

public slots:
    void record_failed_login(QString remoteIP);

};

#endif // FIREWALLCONTROLLER_H