#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
class DatabaseController : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject *parent = nullptr);
    ~DatabaseController();
    QSqlDatabase db;
signals:

public slots:
    void load_database(QString filepath);
};

#endif // DATABASECONTROLLER_H