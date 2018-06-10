#include "processcontroller.h"
#include "../src_process/processlauncherthread.h"
#include <QtDebug>
ProcessController::ProcessController(QObject *parent) : QObject(parent)
{

}

int ProcessController::spawn_internal_process(QString relativeFile, QStringList args)
{
    newProcessLauncherThread = new ProcessLauncherThread(relativeFile, args, "internal");
    int new_idx = 0;
    while (m_processes.keys().contains(new_idx)) { new_idx++; }
    this->m_processes[m_processes.count()] = newProcessLauncherThread;
    QObject::connect(newProcessLauncherThread, &ProcessLauncherThread::outputWritten, this, &ProcessController::handleProcessOutput);
    newProcessLauncherThread->start();
    return new_idx;
}

void ProcessController::handleProcessOutput(QByteArray output)
{
    ProcessLauncherThread* thread = qobject_cast<ProcessLauncherThread*>(sender());
    qDebug() << "Process Output:" << output;
}
