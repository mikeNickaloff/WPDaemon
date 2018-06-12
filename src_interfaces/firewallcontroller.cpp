#include "firewallcontroller.h"
#include "databasecontroller.h"
#include <QDateTime>
#include <QHostAddress>
#include <QObject>
#include <QtDebug>
FirewallController::FirewallController(QObject *parent, DatabaseController *i_db) : QObject(parent), m_db(i_db)
{
    // frequency between logins
    FAILED_LOGIN_INTERVAL = 300;

    // number of failed logins occuring within
    // frequency
    FAILED_LOGIN_COUNT = 3;

    // how long to block the IP address (in seconds)
    //  when exceeding  FAILED_LOGIN_COUNT within
    //  FAILED_LOGIN_INTERVAL seconds
    //
    FAILED_LOGIN_BAN_TIME = 10800;



}

bool FirewallController::isBanned(QString remoteIP)
{
    qint64 ntime = QDateTime::currentSecsSinceEpoch();
     if (m_bans.keys().contains(remoteIP)) {
         if (m_bans[remoteIP] > ntime) {
           return true;
         } else {
           m_bans.remove(remoteIP);
           return false;
         }
     } else {
       return false;
     }
  /*  if (ban_list.keys().contains(remoteIP)) {
        QDateTime time = ban_list.value(remoteIP);
        if (time.secsTo(QDateTime::currentDateTime()) < 0) {
            ban_list.remove(remoteIP);
            return false;
        } else {
            return true;
        }
    } */
    return false;

}

void FirewallController::record_failed_login(QString remoteIP)
{
    qDebug() << "Failed Login from " << remoteIP;
    int i = 0;
    while ((m_hosts.keys().contains(i)) || (m_hosts.value(i) == remoteIP)) {
        i++;
    }
    int hostId = i;
    qint64 ntime;
    ntime = QDateTime::currentSecsSinceEpoch();
    if (!m_hosts.values().contains(remoteIP)) {
         m_hosts[hostId] = remoteIP;
         m_fails[hostId] = 0;
         m_times[hostId] = ntime;

         qDebug() << "Added new Host Entry" << remoteIP << 0 << ntime;

    }
    QDateTime lastTime = QDateTime::fromSecsSinceEpoch(m_times[hostId]);
    QDateTime nTime = QDateTime::fromSecsSinceEpoch(ntime);
    if (lastTime.secsTo(nTime) > FAILED_LOGIN_INTERVAL) {
        m_fails[hostId] = 0;
    }
    m_fails[hostId]++;
    m_times[hostId] = ntime;
    int failCount = m_fails[hostId];
    if (failCount > FAILED_LOGIN_COUNT) {
        m_bans[remoteIP] = ntime + FAILED_LOGIN_BAN_TIME;
        qDebug() << remoteIP << "has been banned";
    }

}
