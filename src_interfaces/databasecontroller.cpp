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
DatabaseController::DatabaseController(QObject *parent, AssetUnpacker* i_unpacker) : QObject(parent), m_assets(i_unpacker)
{
    this->load_database(qApp->applicationDirPath().append(QDir::separator()).append("database.db"));
}

DatabaseController::~DatabaseController()
{
    db.close();
    delete &db;
}

void DatabaseController::load_database(QString filepath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(filepath);
    bool ok = db.open();
    if (ok) {
        if (!db.tables().contains("USERS")) {
            db.exec("CREATE table USERS (ID int primary key, USERNAME text, PASSWORD text)");
            db.exec("INSERT INTO USERS VALUES(1, 'ADMIN', 'DEFAULTPASSWORD')");
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
                  << "config"
                  << "core"
                  << "cron"
                  << "db"
                  << "embed"
                  << "eval"
                  << "eval-file"
                  << "export"
                  << "help"
                  << "import"
                  << "language"
                  << "media"
                  << "menu"
                  << "network"
                  << "option"
                  << "package"
                  << "plugin"
                  << "post"
                  << "post-type"
                  << "rewrite"
                  << "role"
                  << "scaffold"
                  << "search-replace"
                  << "server"
                  << "shell"
                  << "sidebar"
                  << "site"
                  << "super-admin"
                  << "taxonomy"
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
                          << "Generates and reads the wp-config.php file."
                          << "Downloads, installs, updates, and manages a WordPress installation."
                          << "Tests, runs, and deletes WP-Cron events; manages WP-Cron schedules."
                          << "Performs basic database operations using credentials stored in wp-config.php."
                          << "Inspects oEmbed providers, clears embed cache, and more."
                          << "Executes arbitrary PHP code."
                          << "Loads and executes a PHP file."
                          << "Exports WordPress content to a WXR file."
                          << "Get help on WP-CLI, or on a specific command."
                          << "Imports content from a given WXR file."
                          << "Installs, activates, and manages language packs."
                          << "Imports files as attachments, regenerates thumbnails, or lists registered image sizes."
                          << "Lists, creates, assigns, and deletes the active theme's navigation menus."
                          << "Perform network-wide operations."
                          << "Retrieves and sets site options, including plugin and WordPress settings."
                          << "Lists, installs, and removes WP-CLI packages."
                          << "Manages plugins, including installs, activations, and updates."
                          << "Manages posts, content, and meta."
                          << "Retrieves details on the site's registered post types."
                          << "Lists or flushes the site's rewrite rules, updates the permalink structure."
                          << "Manages user roles, including creating new roles and resetting to defaults."
                          << "Generates code for post types, taxonomies, plugins, child themes, etc."
                          << "Searches/replaces strings in the database."
                          << "Launches PHP's built-in web server for a specific WordPress installation."
                          << "Opens an interactive PHP console for running and testing PHP code."
                          << "Lists registered sidebars."
                          << "Creates, deletes, empties, moderates, and lists one or more sites on a multisite installation."
                          << "Lists, adds, or removes super admin users on a multisite installation."
                          << "Retrieves information about registered taxonomies."
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
            qDebug() << "Setting up permissions..";

        }
    }
    //qDebug() <<  executeSelectQuery("PERMSTATES", (QStringList() << "NAME" << "DESCRIPTION"), QString(""));
}

QVector< QVector<QString> > DatabaseController::executeSelectQuery(QString table, QStringList columns, QString extraParameters)
{
    QSqlQuery q;
    QVector< QVector<QString> > rv;
    q.exec(QString("select %1 from %2 %3").arg(columns.join(",")).arg(table).arg(extraParameters));
    //qDebug() << "Running query" <<QString("select %1 from %2 %3;").arg(columns.join(",")).arg(table).arg(extraParameters);

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

