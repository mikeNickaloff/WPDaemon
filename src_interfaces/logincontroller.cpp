#include "logincontroller.h"
#include "databasecontroller.h"
#include <QVector>
#include <QtDebug>
#include <QVectorIterator>
LoginController::LoginController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{
    this->hello_str = "hello, world!";
    loggedIn = false;
}

bool LoginController::check_login(QString username, QString password)
{


    if (m_db->executeSelectQuery("USERS", (QStringList() << "USERNAME" << "PASSWORD"), QString("where USERNAME like '%1' and PASSWORD like '%2'").arg(username).arg(password)).count() > 0) {
        loggedIn = true;

       QVector<QVector<QString> > rv(m_db->executeSelectQuery("USERS", (QStringList() << "USERS.ID" << "USERNAME" << "ASSIGNMENTS.PERMISSION" << "ASSIGNMENTS.ASSIGNED" << "PERMSTATES.DESCRIPTION"), "inner join ASSIGNMENTS ON UID=USERS.ID inner join PERMSTATES on ASSIGNMENTS.PERMISSION=PERMSTATES.PERMISSION"));
       QVectorIterator<QVector<QString > > i(rv);
       while (i.hasNext()) {
           QVector<QString> rowData(i.next());
           this->assignments[rowData.at(2).toInt()] = static_cast<bool>(rowData.at(3).toInt());
           this->assignment_descriptions[rowData.at(2).toInt()] = rowData.at(4);
           this->m_uid = rowData.at(0).toInt();
           this->m_username = rowData.at(1);
       }


        return true;
    }
    loggedIn = false;
    return false;
}

void LoginController::hello()
{

}
