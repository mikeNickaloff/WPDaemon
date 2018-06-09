#ifndef PROCESSLAUNCHERTHREAD_H
#define PROCESSLAUNCHERTHREAD_H

#include <QObject>
#include <QThread>

class ProcessLauncherThread : public QThread
{
public:
    ProcessLauncherThread();
public slots:
   QByteArray run_internal_script(QString scriptFile, QStringList scriptArgs);
};

#endif // PROCESSLAUNCHERTHREAD_H