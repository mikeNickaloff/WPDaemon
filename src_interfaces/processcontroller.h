#ifndef PROCESSCONTROLLER_H
#define PROCESSCONTROLLER_H

#include <QObject>
#include <QHash>
class ProcessLauncherThread;
class ProcessController : public QObject
{
    Q_OBJECT
public:
    explicit ProcessController(QObject *parent = nullptr);
    QHash<int, ProcessLauncherThread*> m_processes;
    ProcessLauncherThread* newProcessLauncherThread;

signals:

public slots:
};

#endif // PROCESSCONTROLLER_H