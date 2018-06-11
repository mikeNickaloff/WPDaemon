#ifndef ASSETUNPACKER_H
#define ASSETUNPACKER_H

#include <QObject>

class AssetUnpacker : public QObject
{
    Q_OBJECT
public:
    explicit AssetUnpacker(QObject *parent = nullptr);
QString appDirectory(QString subdirectory = "");
signals:

public slots:
    void unpack(QString resourceDir, QString targetDir);
};

#endif // ASSETUNPACKER_H