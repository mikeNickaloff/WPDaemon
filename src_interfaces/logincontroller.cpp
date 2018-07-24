#include "logincontroller.h"
#include "databasecontroller.h"
#include <QVector>
#include <QtDebug>
#include <QVectorIterator>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QDateTime>
LoginController::LoginController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{
  this->hello_str = "hello, world!";
  loggedIn = false;
}

bool LoginController::check_login(QString username, QString password)
{


  if (m_db->executeSelectQuery("USERS", (QStringList() << "USERNAME" << "PASSWORD"), QString("where USERNAME like '%1' and PASSWORD like '%2'").arg(m_db->toHex(username)).arg(m_db->toHex(m_db->sha512(password)))).count() > 0) {
      loggedIn = true;


      //populate permissions, descriptions, etc on a per user basis
      // this will allow for future extending of the code if the need
      // arises to have language support etc then the descriptions can
      // be populated based on the selected language or the descriptions
      // can be more specific for administrators than for operators etc
      // it wastes about 2kb of total memory to store and is only requested
      // once on login so i think its okay to keep

      QVector<QVector<QString> > rv(m_db->executeSelectQuery("USERS", (QStringList() << "USERS.ID" << "USERNAME" << "ASSIGNMENTS.PERMISSION" << "ASSIGNMENTS.ASSIGNED" << "PERMSTATES.DESCRIPTION" << "PERMSTATES.NAME"), QString("inner join ASSIGNMENTS ON UID=USERS.ID inner join PERMSTATES on ASSIGNMENTS.PERMISSION=PERMSTATES.PERMISSION where USERNAME like '%1'").arg(m_db->toHex(username))));
      QVectorIterator<QVector<QString > > i(rv);
      while (i.hasNext()) {
          QVector<QString> rowData(i.next());
          this->assignments[rowData.at(2).toInt()] = static_cast<bool>(rowData.at(3).toInt());
          this->assignment_names[rowData.at(2).toInt()] = rowData.at(5);
          this->assignment_id_names[rowData.at(5)] = rowData.at(2).toInt();
          this->assignment_descriptions[rowData.at(2).toInt()] = rowData.at(4);
          this->m_uid = rowData.at(0).toInt();
          this->m_username = m_db->fromHex(rowData.at(1));
        }
      //end of permission assignment population
      // qDebug() << "Successful Login";
      return true;
    }
  loggedIn = false;
  return false;
}

bool LoginController::check_token(QString token)
{
  QVector<QVector<QString> > queryResult(m_db->executeSelectQuery("SESSIONS", (QStringList() << "UID" << "TOKEN" << "SESSIONDATA"), QString("where TOKEN like '%1'").arg(m_db->toHex(token))));
  if (queryResult.count() > 0) {
      if (queryResult.first().length() > 2) {

          qint64 expireTime = queryResult.first().at(2).toInt();
          qint64 currentTime = QDateTime::currentSecsSinceEpoch();
          if (expireTime > currentTime) {
              loggedIn = true;
              QSqlQuery query = m_db->db.exec(QString("delete from SESSIONS where TOKEN like '%1'").arg(m_db->toHex(token)));
              query.finish();

              //populate permissions, descriptions, etc on a per user basis
              // this will allow for future extending of the code if the need
              // arises to have language support etc then the descriptions can
              // be populated based on the selected language or the descriptions
              // can be more specific for administrators than for operators etc
              // it wastes about 2kb of total memory to store and is only requested
              // once on login so i think its okay to keep

              QVector<QVector<QString> > rv(m_db->executeSelectQuery("USERS", (QStringList() << "USERS.ID" << "USERNAME" << "ASSIGNMENTS.PERMISSION" << "ASSIGNMENTS.ASSIGNED" << "PERMSTATES.DESCRIPTION" << "PERMSTATES.NAME"), "inner join ASSIGNMENTS ON UID=USERS.ID inner join PERMSTATES on ASSIGNMENTS.PERMISSION=PERMSTATES.PERMISSION"));
              QVectorIterator<QVector<QString > > i(rv);
              while (i.hasNext()) {
                  QVector<QString> rowData(i.next());
                  this->assignments[rowData.at(2).toInt()] = static_cast<bool>(rowData.at(3).toInt());
                  this->assignment_names[rowData.at(2).toInt()] = rowData.at(5);
                  this->assignment_id_names[rowData.at(5)] = rowData.at(2).toInt();
                  this->assignment_descriptions[rowData.at(2).toInt()] = rowData.at(4);
                  this->m_uid = rowData.at(0).toInt();
                  this->m_username = m_db->fromHex(rowData.at(1));
                }
              //end of permission assignment population

            } else {
              loggedIn = false;
            }
        } else {
          loggedIn = false;
        }
    } else {
      loggedIn = false;
    }
  return loggedIn;
}

QString LoginController::new_token(QString oldToken)
{
  QSqlQuery query = m_db->db.exec(QString("delete from SESSIONS where TOKEN like '%1'").arg(m_db->toHex(oldToken)));
  query.finish();
  QVariantList v;
  QUuid newTokenUUid;
  QString newToken = newTokenUUid.createUuid().toString();
  qint64 expireTime;
  expireTime = QDateTime::currentSecsSinceEpoch();
  expireTime += 240;
  int newid = m_db->executeSelectQuery("SESSIONS", (QStringList() << "UID" << "TOKEN"), QString("")).count();
  v.append(QVariant::fromValue(newid));
  v.append(QVariant::fromValue(m_uid));
  v.append(QVariant::fromValue(newToken));
  v.append(QVariant::fromValue(expireTime));

  m_db->executeInsert("SESSIONS", v);
  return newToken;
}

void LoginController::hello()
{

}
