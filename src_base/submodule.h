#ifndef SUBMODULE_H
#define SUBMODULE_H

#include <QObject>
#include "../src_interfaces/processcontroller.h"
#include "../src_process/processlauncherthread.h"
#include <QThread>
class SubmoduleCommand;
class ProcessController;
class ProcessLauncherThread;
class Submodule : public QObject
{
    Q_OBJECT
public:
    explicit Submodule(QObject *parent = nullptr);
    QString moduleName;
    QHash<int, SubmoduleCommand*> commands;
    QVariant get_command_dump(QString subproperty);
    ProcessLauncherThread* processLauncher;

signals:

public slots:


};

#endif // SUBMODULE_H