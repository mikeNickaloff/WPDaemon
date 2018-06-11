#include "assetunpacker.h"
#include <QCoreApplication>
#include <QDir>
#include <iostream>

AssetUnpacker::AssetUnpacker(QObject *parent) : QObject(parent)
{

QDir dir(":/res_scripts");
dir.mkdir(appDirectory("scripts"));
QFileInfoList list = dir.entryInfoList();
     std::cout << "     Bytes Filename" << std::endl;
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                 .arg(fileInfo.fileName()));
         QFile f1(QString(":/res_scripts/%1").arg(fileInfo.fileName()));

         f1.copy(QString(appDirectory("scripts").append(QDir::separator()).append(fileInfo.fileName())));
         std::cout << std::endl;
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
