#include "logincontroller.h"
#include "databasecontroller.h"
#include <QVector>
#include <QtDebug>
LoginController::LoginController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{
    this->hello_str = "hello, world!";
    loggedIn = false;
}

bool LoginController::check_login(QString username, QString password)
{


    if (m_db->executeQuery("USERS", (QStringList() << "USERNAME" << "PASSWORD"), QString("where USERNAME like '%1' and PASSWORD like '%2'").arg(username).arg(password)).count() > 0) {
        loggedIn = true;
        return true;
    }
    loggedIn = false;
    return false;
}

void LoginController::hello()
{

}
