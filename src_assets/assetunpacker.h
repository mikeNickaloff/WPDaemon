#ifndef ASSETUNPACKER_H
#define ASSETUNPACKER_H

#include <QObject>

class AssetUnpacker : public QObject
{
    Q_OBJECT
public:
    explicit AssetUnpacker(QObject *parent = nullptr);

signals:

public slots:
    QString appDirectory(QString subdirectory = "");
};

#endif // ASSETUNPACKER_H