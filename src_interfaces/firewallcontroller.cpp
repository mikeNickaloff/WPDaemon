#include "firewallcontroller.h"
#include "databasecontroller.h"
#include <QDateTime>
#include <QHostAddress>
FirewallController::FirewallController(QObject *parent, DatabaseController *i_db) : QObject(parent), m_db(i_db)
{

}

bool FirewallController::isBanned(QString remoteIP)
{

    if (ban_list.keys().contains(remoteIP)) {
        QDateTime time = ban_list.value(remoteIP);
        if (time.secsTo(QDateTime::currentDateTime()) < 0) {
            ban_list.remove(remoteIP);
            return false;
        } else {
            return true;
        }
    }
    return false;

}

void FirewallController::record_failed_login(QString remoteIP)
{
    qDebug() << "Failed Login from " << remoteIP;
    // need to fix this code and
    // related members due to seg fault somewhere
    //  (or some other error)  causes abort :/
    // ... might be a typo or something.
    // or the #DEFINE values

    /*if (this->last_failed_login.keys().contains(remoteIP)) {
        QDateTime lastFail =  this->last_failed_login.value(remoteIP);
        if ((int)lastFail.secsTo(QDateTime::currentDateTime()) < (int)FAILED_LOGIN_INTERVAL) {
            this->last_failed_login[remoteIP] = QDateTime::currentDateTime();
            this->failed_login_count[remoteIP] = this->failed_login_count.value(remoteIP,1) + 1;
            if (this->failed_login_count.value(remoteIP) > (int)FAILED_LOGIN_COUNT) {
                this->ban_list[remoteIP] = QDateTime::currentDateTime().addSecs(FAILED_LOGIN_BAN_TIME);
                qDebug() << remoteIP << "has been banned until" << ban_list.value(remoteIP);
            }
        } else {
            this->last_failed_login[remoteIP] = QDateTime::currentDateTime();
            this->failed_login_count[remoteIP] = 1;
        }
    } else {
        this->last_failed_login[remoteIP] = QDateTime::currentDateTime();
        this->failed_login_count[remoteIP] = 1;
    } */
}
