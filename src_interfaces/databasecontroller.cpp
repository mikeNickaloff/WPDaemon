#include "databasecontroller.h"
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QDir>
DatabaseController::DatabaseController(QObject *parent) : QObject(parent)
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

    }
}
