#ifndef PROCESSCONTROLLER_H
#define PROCESSCONTROLLER_H

#include <QObject>

class ProcessController : public QObject
{
    Q_OBJECT
public:
    explicit ProcessController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PROCESSCONTROLLER_H