#ifndef FIREWALLCONTROLLER_H
#define FIREWALLCONTROLLER_H

#include <QObject>
#include <QHostAddress>
#include <QDateTime>

// frequency between logins
#define FAILED_LOGIN_INTERVAL 300

// number of failed logins occuring within
// frequency
#define FAILED_LOGIN_COUNT 3

// how long to block the IP address (in seconds)
//  when exceeding  FAILED_LOGIN_COUNT within
//  FAILED_LOGIN_INTERVAL seconds
//
#define FAILED_LOGIN_BAN_TIME 10800


class DatabaseController;
class FirewallController : public QObject
{
    Q_OBJECT
public:
    explicit FirewallController(QObject *parent = nullptr, DatabaseController* i_db = nullptr);
    DatabaseController* m_db;
    QHash<QString, QDateTime> last_failed_login;
    QHash<QString, int> failed_login_count;
    QHash<QString, QDateTime> ban_list;
    bool isBanned(QString remoteIP);
signals:

public slots:
    void record_failed_login(QString remoteIP);
};

#endif // FIREWALLCONTROLLER_H