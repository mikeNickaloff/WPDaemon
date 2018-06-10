#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QHash>
#include <QUuid>
class LoginController : public QObject
{
    Q_OBJECT
public:
    explicit LoginController(QObject *parent = nullptr);
    QHash<QUuid, QString> loginTokens;
signals:

public slots:
};

#endif // LOGINCONTROLLER_H