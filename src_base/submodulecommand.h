#ifndef SUBMODULECOMMAND_H
#define SUBMODULECOMMAND_H

#include <QObject>

class SubmoduleCommand : public QObject
{
    Q_OBJECT
public:
    explicit SubmoduleCommand(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SUBMODULECOMMAND_H