#include "configcontroller.h"
#include <QCoreApplication>
#include <QSettings>
#include <QDir>
#include <QtDebug>

ConfigController::ConfigController(QObject *parent) : QObject(parent)
{

}

QSettings* ConfigController::settings()
{
 QSettings* _settings = new QSettings(qApp->applicationDirPath().append(QDir::separator()).append("wpdaemon.conf"), QSettings::IniFormat);
 return _settings;
}
