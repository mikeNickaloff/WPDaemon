#include "databasecontroller.h"
#include "../src_assets/assetunpacker.h"
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QDir>
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

    }
}
