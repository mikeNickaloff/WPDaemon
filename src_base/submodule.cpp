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
// Synopsis Parser
// [value]             (\[\S+\]\B)
// <required>          (\<\S+\>\B)
// [--option=<value>]  (\[\S+\=<\S+\>\]\B)


//  to match all of a type in a row, add + to the end


QVariant Submodule::get_command_dump(QString subproperty)
{
    this->processLauncher = new ProcessLauncherThread("get_submodule_commands.sh", (QStringList() << moduleName), "internal");
    QByteArray output;
    output.append(processLauncher->run_internal_script("get_submodule_commands.sh", (QStringList() << moduleName << subproperty)));

    qDebug() << output;
    return QVariant::fromValue(output);

}

QVariant Submodule::get_synopsis(QString subproperty, int subcommand_index)
{
    this->processLauncher = new ProcessLauncherThread("get_submodule_commands.sh", (QStringList() << moduleName), "internal");
    QByteArray output;
    output.append(processLauncher->run_internal_script("get_submodule_commands.sh", (QStringList() << moduleName << subproperty << QString("%1").arg(subcommand_index))));

    qDebug() << output;
    return QVariant::fromValue(output);
}


void Submodule::add_command(QString i_name, QString i_desc, QString i_synopsis)
{
    int newIdx = 0;
    while (commands.keys().contains(newIdx)) { newIdx++; }

    new_command = new SubmoduleCommand(this, i_name, i_desc, i_synopsis);
    commands[newIdx] = new_command;


}