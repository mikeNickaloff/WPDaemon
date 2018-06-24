#include "configcontroller.h"
#include <QCoreApplication>
#include <QSettings>
#include <QDir>

ConfigController::ConfigController(QObject *parent) : QObject(parent)
{

}

QSettings* ConfigController::settings()
{
 QSettings* _settings = new QSettings(qApp->applicationDirPath().append(QDir::separator()).append("config").append(QDir::separator()).append("wpdaemon.conf"), QSettings::IniFormat);
// _settings->setValue("enable_ssl", "true");
// _settings->setValue("ssl_certificate_file", qApp->applicationDirPath().append(QDir::separator()).append("cert.pem"));
// _settings->setValue("ssl_key_file", qApp->applicationDirPath().append(QDir::separator()).append("key.pem"));
 return _settings;
}
