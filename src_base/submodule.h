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
    SubmoduleCommand* new_command;
    QVariant get_synopsis(QString subproperty, int subcommand_index);
signals:

public slots:
    void add_command(QString i_name, QString i_desc, QString i_synopsis);
};

#endif // SUBMODULE_H