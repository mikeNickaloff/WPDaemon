#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QHash>
#include <QUuid>
class DatabaseController;
class LoginController : public QObject
{
    Q_OBJECT
public:
    explicit LoginController(QObject *parent = nullptr, DatabaseController* i_db = nullptr);
    QHash<QUuid, QString> loginTokens;
    DatabaseController* m_db;
signals:

public slots:
private:
    QString hello_str;
private slots:
    void hello();
};

#endif // LOGINCONTROLLER_H