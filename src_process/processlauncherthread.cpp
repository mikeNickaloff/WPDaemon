#include "processlauncherthread.h"
#include <QProcess>
#include <QtDebug>
#include <QDir>
#include <QCoreApplication>

ProcessLauncherThread::ProcessLauncherThread()
{

}
QByteArray ProcessLauncherThread::run_internal_script(QString scriptFile, QStringList scriptArgs)
{
    QString program = qApp->applicationDirPath().append(QDir::separator()).append("scripts").append(QDir::separator()).append(QString(scriptFile));

    QProcess *myProcess = new QProcess(parent());
    myProcess->setWorkingDirectory(qApp->applicationDirPath().append(QDir::separator()).append("scripts"));

    myProcess->start("/bin/bash", (QStringList() << program << scriptArgs));
    myProcess->setReadChannelMode(QProcess::ForwardedOutputChannel);
    if (!myProcess->waitForStarted(3000)) {
        qDebug() << "Failed";
    } else {
        qDebug() << myProcess->arguments();
        qDebug() << myProcess->state();

    }
    if (!myProcess->waitForFinished(120000)) {
        qDebug() << "Took too long";
    } else {
        qDebug() << myProcess->readAll();
    }
    return myProcess->readAllStandardOutput();
}