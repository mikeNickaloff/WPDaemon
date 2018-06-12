#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QVector>
class AssetUnpacker;
class DatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr, AssetUnpacker* i_unpacker = nullptr);
    ~DatabaseController();
    AssetUnpacker* m_assets;
    QSqlDatabase db;
signals:

public slots:
    void load_database(QString filepath);
    QVector<QVector<QString> > executeSelectQuery(QString table, QStringList columns, QString extraParameters);


};

#endif // DATABASECONTROLLER_H