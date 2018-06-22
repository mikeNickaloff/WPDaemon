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
    newProcessLauncherThread->processThreadId = new_idx;
    newProcessLauncherThread->start();
    return new_idx;
}

void ProcessController::handleProcessOutput(int processThreadId, QByteArray output)
{
    ProcessLauncherThread* thread = qobject_cast<ProcessLauncherThread*>(sender());

    QString output_str = QString::fromLocal8Bit(output);
    emit this->outputFromProcess(processThreadId, output_str);
     // qDebug() << "Process Output:" << output;
}
