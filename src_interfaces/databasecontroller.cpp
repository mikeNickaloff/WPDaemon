#include "databasecontroller.h"
#include "../src_assets/assetunpacker.h"
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QDir>
#include <QSqlQuery>
#include <QVariantList>
#include <QtDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <QVector>
#include <QCryptographicHash>
DatabaseController::DatabaseController(QObject *parent, AssetUnpacker* i_unpacker) : QObject(parent), m_assets(i_unpacker)
{
  this->load_database(qApp->applicationDirPath().append(QDir::separator()).append("database.db"));
}

DatabaseController::~DatabaseController()
{
  db.close();
  delete &db;
}

QString DatabaseController::toHex(QString plainText)
{
  QByteArray bytearray(plainText.toLocal8Bit());
  QByteArray hexarray(bytearray.toHex());
  QString rv = QString::fromLocal8Bit(hexarray);
  return rv;
}

QString DatabaseController::fromHex(QString hexText)
{
  QByteArray hexarray(hexText.toLocal8Bit());
  QByteArray plainarray(QByteArray::fromHex(hexarray));
  QString rv = QString::fromLocal8Bit(plainarray);
  return rv;
}

QString DatabaseController::sha512(QString plainText)
{
  QCryptographicHash hash(QCryptographicHash::Sha512);
  QByteArray plainArray(plainText.toLocal8Bit());
  QByteArray hashArray(QCryptographicHash::hash(plainArray, QCryptographicHash::Sha512));
  QString rv(QString::fromLocal8Bit(hashArray));
  return rv;
}

void DatabaseController::load_database(QString filepath)
{
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(filepath);
  bool ok = db.open();
  if (ok) {
      if (!db.tables().contains("USERS")) {
          db.exec("CREATE table USERS (ID int primary key, USERNAME text, PASSWORD text)");
          db.exec(QString("INSERT INTO USERS VALUES(1, '%1', '%2')").arg(toHex("ADMIN")).arg(toHex(sha512("DEFAULTPASSWORD"))));

        }
      if (!db.tables().contains("ASSIGNMENTS")) {
          db.exec("CREATE table ASSIGNMENTS (ID int primary key, UID int, PERMISSION int, ASSIGNED int )");



        }
      if (!db.tables().contains("PERMSTATES")) {
          db.exec("CREATE table PERMSTATES (ID int primary key,  PERMISSION int, NAME text, DESCRIPTION text, ENABLED int)");
          db.transaction();
          QSqlQuery q;
          q.prepare("INSERT INTO PERMSTATES VALUES(?, ?, ?, ?, ?)");
          QVariantList ids;


          QVariantList names;
          names << "admin"
                << "cache"
                << "cap"
                << "cli"
                << "comment"
                << "core"
                << "cron"
                << "db"
                << "embed"
                << "export"
                << "import"
                << "language"
                << "media"
                << "menu"
                << "network"
                << "option"
                << "plugin"
                << "post"
                << "post-type"
                << "rewrite"
                << "role"
                << "scaffold"
                << "search-replace"
                << "sidebar"
                << "site"
                << "super-admin"
                << "term"
                << "theme"
                << "transient"
                << "user"
                << "widget";
          QVariantList enabledList;
          while (ids.count() < names.count()) { ids << ids.count(); enabledList << 1; }
          q.addBindValue(ids);
          q.addBindValue(ids);
          q.addBindValue(names);
          QVariantList descriptions;
          descriptions  << "Can add/remove Users and Configure WPDaemon."
                        << "Adds, removes, fetches, and flushes the WP Object Cache object."
                        << "Adds, removes, and lists capabilities of a user role."
                        << "Review current WP-CLI info, check for updates, or see defined aliases."
                        << "Creates, updates, deletes, and moderates comments."
                        << "Downloads, installs, updates, and manages a WordPress installation."
                        << "Tests, runs, and deletes WP-Cron events; manages WP-Cron schedules."
                        << "Performs basic database operations using credentials stored in wp-config.php."
                        << "Inspects oEmbed providers, clears embed cache, and more."
                        << "Exports WordPress content to a WXR file."
                        << "Imports content from a given WXR file."
                        << "Installs, activates, and manages language packs."
                        << "Imports files as attachments, regenerates thumbnails, or lists registered image sizes."
                        << "Lists, creates, assigns, and deletes the active theme's navigation menus."
                        << "Perform network-wide operations."
                        << "Retrieves and sets site options, including plugin and WordPress settings."
                        << "Manages plugins, including installs, activations, and updates."
                        << "Manages posts, content, and meta."
                        << "Retrieves details on the site's registered post types."
                        << "Lists or flushes the site's rewrite rules, updates the permalink structure."
                        << "Manages user roles, including creating new roles and resetting to defaults."
                        << "Generates code for post types, taxonomies, plugins, child themes, etc."
                        << "Searches/replaces strings in the database."
                        << "Lists registered sidebars."
                        << "Creates, deletes, empties, moderates, and lists one or more sites on a multisite installation."
                        << "Lists, adds, or removes super admin users on a multisite installation."
                        << "Manages taxonomy terms and term meta, with create, delete, and list commands."
                        << "Manages themes, including installs, activations, and updates."
                        << "Adds, gets, and deletes entries in the WordPress Transient Cache."
                        << "Manages users, along with their roles, capabilities, and meta."
                        << "Manages widgets, including adding and moving them within sidebars.";

          q.addBindValue(descriptions);
          q.addBindValue(enabledList);
          if (!q.execBatch())
            qDebug() << q.lastError();

          QSqlQuery q2;
          q2.prepare("INSERT INTO ASSIGNMENTS VALUES(?, 1, ?, 1)");
          q2.addBindValue(ids);
          q2.addBindValue(ids);
          if (!q2.execBatch())
            qDebug() << q2.lastError();
          db.commit();
          // qDebug() << "Setting up permissions..";

        }

      if (!db.tables().contains("WEBSITES")) {
          db.exec("CREATE table WEBSITES (ID int primary key, NAME text, PATH text)");
        }
      if (!db.tables().contains("SESSIONS")) {
          db.exec("CREATE table SESSIONS (ID int primary key, UID text, TOKEN text, SESSIONDATA text)");
        }

    }
  // // qDebug() <<  executeSelectQuery("PERMSTATES", (QStringList() << "NAME" << "DESCRIPTION"), QString(""));
}

QVector< QVector<QString> > DatabaseController::executeSelectQuery(QString table, QStringList columns, QString extraParameters)
{
  QSqlQuery q;
  QVector< QVector<QString> > rv;
  q.exec(QString("select %1 from %2 %3").arg(columns.join(",")).arg(table).arg(extraParameters));
  // // qDebug() << "Running query" <<QString("select %1 from %2 %3;").arg(columns.join(",")).arg(table).arg(extraParameters);

  // here to ensure that the first record is captured
  // due to some invalid query results during alpha
  // testing -- this conditional
  //should be checked and removed.
  if (q.isValid()) {
      QVector<QString> nv;
      for (int i=0; i<columns.count(); i++) {
          nv << q.value(i).toString();
        }
      rv.append(nv);
    }


  // should read the entire query result here

  while (q.next()) {
      QVector<QString> nv;
      for (int i=0; i<columns.count(); i++) {
          nv << q.value(i).toString();
        }
      rv.append(nv);


    }


  return rv;
}

void DatabaseController::executeInsert(QString table, QVariantList values)
{
  qDebug() << values;
  if (values.count() > 0) {
      db.transaction();
      QSqlQuery q2;
      QString prepare_statement = "";
          int m = values.count();
          int i = 0;
      foreach (QVariant v, values) {
          prepare_statement.append(" ?");
          i++;
          if (i < m) {
               prepare_statement.append(",");
            }

        }
      q2.prepare(QString("INSERT INTO %1 VALUES(%2)").arg(table).arg(prepare_statement));
      qDebug() << "Prepared statement" << QString("INSERT INTO %1 VALUES(%2)").arg(table).arg(prepare_statement);
      i = 0;
      foreach (QVariant v, values) {

          q2.bindValue(i, v);
          i++;

        }

      if (!q2.execBatch())
        qDebug() << q2.lastError();
      qDebug() << q2.boundValues();

        db.commit();
    }

}

