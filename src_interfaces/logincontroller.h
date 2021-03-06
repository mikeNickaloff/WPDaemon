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
    bool check_login(QString username, QString password);
    bool loggedIn;

    // assigned permissions
    QHash<int, bool> assignments;
    QHash<int, QString> assignment_names;
    QHash<int, QString> assignment_descriptions;
    QHash<QString, int> assignment_id_names;
    int m_uid;
    QString m_username;
    QString current_token;
    bool check_token(QString token);
    QString new_token(QString oldToken);
signals:

public slots:


private:
    QString hello_str;
private slots:
    void hello();

};

#endif // LOGINCONTROLLER_H
