#ifndef PROCESSLAUNCHERTHREAD_H
#define PROCESSLAUNCHERTHREAD_H

#include <QObject>
#include <QThread>

class ProcessLauncherThread : public QThread
{
    Q_OBJECT
public:
    // args:
    // relative path if
    // if process_type = "internal"
    //    then
    //    file = URL relative to app dir
    // if process_type = "external"
    //    then
    //    file = full path
    ProcessLauncherThread(QString file, QStringList args, QString process_type = "internal");

    // global definitions
    QString processType;
    QString processFile;
    QStringList processArgs;

    int processThreadId;
signals:
    void outputWritten(int threadId, QByteArray output);
public slots:
   QByteArray run_internal_script(QString scriptFile, QStringList scriptArgs);
   QByteArray run_external_script(QString scriptFile, QStringList scriptArgs);
protected:
   void run();
};

#endif // PROCESSLAUNCHERTHREAD_H