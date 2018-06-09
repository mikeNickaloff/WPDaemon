#ifndef CLICONTROLLER_H
#define CLICONTROLLER_H

#include <QObject>

class CLIController : public QObject
{
    Q_OBJECT
public:
    explicit CLIController(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CLICONTROLLER_H