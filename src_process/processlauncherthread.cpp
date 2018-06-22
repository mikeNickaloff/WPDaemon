#include "processlauncherthread.h"
#include <QProcess>
#include <QtDebug>
#include <QDir>
#include <QCoreApplication>
#include <QThread>
#include <QObject>

ProcessLauncherThread::ProcessLauncherThread(QString file, QStringList args, QString process_type) : QThread(), processType(process_type), processFile(file), processArgs(args)
{

}

QByteArray ProcessLauncherThread::run_internal_script(QString scriptFile, QStringList scriptArgs)
{
    QString program = qApp->applicationDirPath().append(QDir::separator()).append("scripts").append(QDir::separator()).append(QString(scriptFile));

    QProcess *myProcess = new QProcess(parent());
    myProcess->setWorkingDirectory(qApp->applicationDirPath().append(QDir::separator()).append("scripts"));

    myProcess->start("/bin/bash", (QStringList() << program << scriptArgs));
   // myProcess->setReadChannelMode(QProcess::ForwardedOutputChannel);
    if (!myProcess->waitForStarted(3000)) {
         // qDebug() << "Failed";
    } else {
         // qDebug() << myProcess->arguments();
         // qDebug() << myProcess->state();

    }
    if (!myProcess->waitForFinished(-1)) {
         // qDebug() << "Took too long";
    } else {
        // // qDebug() << myProcess->readAll();
        return myProcess->readAll();
    }
    return myProcess->readAll();
}

QByteArray ProcessLauncherThread::run_external_script(QString scriptFile, QStringList scriptArgs)
{
    QString program = scriptFile;

    QProcess *myProcess = new QProcess(parent());
    myProcess->setWorkingDirectory(qApp->applicationDirPath());

    myProcess->start("/bin/bash", (QStringList() << program << scriptArgs));
   // myProcess->setReadChannelMode(QProcess::ForwardedOutputChannel);
    if (!myProcess->waitForStarted(3000)) {
         // qDebug() << "Failed";
    } else {
         // qDebug() << myProcess->arguments();
         // qDebug() << myProcess->state();

    }
    if (!myProcess->waitForFinished(120000)) {
         // qDebug() << "Took too long";
    } else {
         // qDebug() << myProcess->readAll();
    }
    return myProcess->readAllStandardOutput();
    //return myProcess->readAll();
}

void ProcessLauncherThread::run()
{
    QByteArray output;

    if (processType == "internal") {  output = run_internal_script(processFile, processArgs); }
    if (processType == "external") {  output = run_external_script(processFile, processArgs); }

    emit outputWritten(this->processThreadId, output);
}