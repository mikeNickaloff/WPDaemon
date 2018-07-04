#include "websitecontroller.h"
#include "databasecontroller.h"
#include "../src_base/website.h"
#include <QVector>
#include <QVariant>
#include <QVariantList>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

WebsiteController::WebsiteController(QObject *parent, DatabaseController *i_db) : QObject(parent), db(i_db)
{
  QVector<QVector<QString> > rv(db->executeSelectQuery("WEBSITES", (QStringList() << "NAME" << "PATH"), QString("")));
  QVectorIterator<QVector<QString > > i(rv);
  while (i.hasNext()) {
      QVector<QString> rowData(i.next());
      qDebug() << rowData;
      this->websites[rowData.at(0)] = rowData.at(1);
    }

}

void WebsiteController::add_site(QString i_name, QString i_path)
{
  QVariantList v;
  v.append(QVariant::fromValue(websites.count()));
  v.append(QVariant::fromValue(i_name));
  v.append(QVariant::fromValue(i_path));
 QString query = QString("INSERT INTO WEBSITES VALUES(%1, '%2', '%3');").arg(websites.count()).arg(i_name.remove("'")).arg(i_path);
 QSqlQuery res = db->db.exec(query);
  this->websites[i_name] = i_path;
}
