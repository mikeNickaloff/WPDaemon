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
  this->currentCommand = nullptr;
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

     // qDebug() << output;
    return QVariant::fromValue(output);

}

QVariant Submodule::get_synopsis(QString subproperty, int subcommand_index)
{
    this->processLauncher = new ProcessLauncherThread("get_submodule_commands.sh", (QStringList() << moduleName), "internal");
    QByteArray output;
    output.append(processLauncher->run_internal_script("get_submodule_commands.sh", (QStringList() << moduleName << subproperty << QString("%1").arg(subcommand_index))));

     // qDebug() << output;
    return QVariant::fromValue(output);
}

int Submodule::set_current_command(QString cmd_name)
{
    QHash<int, SubmoduleCommand*>::const_iterator i = this->commands.constBegin();
     // qDebug() << "Checking for" << cmd_name << "in" << commands.values();
    while (i != this->commands.constEnd()) {
        SubmoduleCommand* tmp_cmd = i.value();
        if (tmp_cmd->name == cmd_name) {
            this->currentCommand = tmp_cmd;
            return i.key();
        } else {
          // qDebug() << tmp_cmd->name << "does not match " << cmd_name;
        }
        i++;
    }
    this->currentCommand = nullptr;
    return -1;
}

QString Submodule::toString()
{
    QString rv;
    rv.append(moduleName);
    rv.append(" ");
    if (currentCommand != nullptr) {
        rv.append(currentCommand->toString());
    }
    return rv;
}


void Submodule::add_command(QString i_name, QString i_desc, QString i_synopsis)
{
    int newIdx = 0;
    while (commands.keys().contains(newIdx)) { newIdx++; }

    new_command = new SubmoduleCommand(this, i_name, i_desc, i_synopsis);
    new_command->name.remove(0, 1);
    new_command->name.chop(1);
    commands[newIdx] = new_command;


}
