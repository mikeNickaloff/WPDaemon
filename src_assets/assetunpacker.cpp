#include "assetunpacker.h"
#include <QCoreApplication>
#include <QDir>
#include <iostream>

AssetUnpacker::AssetUnpacker(QObject *parent) : QObject(parent)
{
unpack("res_scripts", "scripts");
unpack("res_html", "public");
unpack("res_python", "python");

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
