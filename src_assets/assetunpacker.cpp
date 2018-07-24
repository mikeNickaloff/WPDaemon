#include "assetunpacker.h"
#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QtDebug>

AssetUnpacker::AssetUnpacker(QObject *parent) : QObject(parent)
{
unpack("res_scripts", "scripts");
unpack("res_html", "public");
unpack("res_python", "python");
QFile confFile(qApp->applicationDirPath().append(QDir::separator()).append("wpdaemon.conf"));
if (!confFile.exists()) {
     qDebug() << "WELCOME TO WPDAEMON\n" << "-------------\n" << "A new file called wpdaemon.conf  has been created in the directory containing the WPDaemon Binary\n" << qApp->applicationDirPath().append(QDir::separator()).append("wpdaemon.conf") << "\n" << "\n" << "You must now do one of the following actions to properly setup WPDaemon:\n\n" << "1)  Modify WPDaemon.conf and change the ssl_certificate_file  and ssl_key_file settings to point to a valid SSL certificate / key pair\n" << "- OR -" << "Place a valid SSL Certificate in the WPDaemon folder with the name 'cert.pem'  and the corosponding key in the same folder with the name 'key.pem'" << "\n\n" << "*  NOTE: If you choose (option 1) , you must also create a symbolic/hard link or hard copy the certificate and key to match the names provided in (option 2).  This process will not be required at all starting with the first beta release, and will be replaced with an interactive prompt. ";
unpack("res_defaults", ".");
  }

}

QString AssetUnpacker::appDirectory(QString subdirectory)
{
    if (subdirectory == "") {
        return qApp->applicationDirPath();
    } else {
      return    qApp->applicationDirPath().append(QDir::separator()).append(subdirectory);
    }
}

void AssetUnpacker::unpack(QString resourceDir, QString targetDir)
{
    QDir dir(QString(":/%1").arg(resourceDir));
    QDir tgt(appDirectory(""));
    bool ok = tgt.mkpath(appDirectory(targetDir));
    if (resourceDir == "res_html") {
        QDir css(appDirectory("public"));
        css.mkpath("css");
        css.mkpath("webfonts");
    }
    QFileInfoList list = dir.entryInfoList();
         std::cout << "     Bytes Filename" << std::endl;
         for (int i = 0; i < list.size(); ++i) {
             QFileInfo fileInfo = list.at(i);
             std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                     .arg(fileInfo.fileName()));
             QFile r1 (QString(appDirectory(targetDir).append(QDir::separator()).append(fileInfo.fileName())));
             r1.remove();
             QFile f1(QString(":/%2/%1").arg(fileInfo.fileName()).arg(resourceDir));

             f1.copy(QString(appDirectory(targetDir).append(QDir::separator()).append(fileInfo.fileName())));
             QFile f2(QString(appDirectory(targetDir).append(QDir::separator()).append(fileInfo.fileName())));
             f2.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);
             std::cout << std::endl;
         }
}
