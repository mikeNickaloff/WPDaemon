#include "submodule.h"
#include "submodulecommand.h"
#include <QHash>
#include "../src_interfaces/processcontroller.h"
#include "../src_interfaces/clicontroller.h"
#include "../src_process/processlauncherthread.h"
#include <QtDebug>
#include <QObject>
#include <QByteArray>
#include <QThread>
Submodule::Submodule(QObject *parent) : QObject(parent)
{

}

QVariant Submodule::get_command_dump(QString subproperty)
{
    this->processLauncher = new ProcessLauncherThread("get_submodule_commands.sh", (QStringList() << moduleName), "internal");
    QByteArray output;
    output.append(processLauncher->run_internal_script("get_submodule_commands.sh", (QStringList() << moduleName << subproperty)));

    qDebug() << output;
return QVariant::fromValue(output);

}


