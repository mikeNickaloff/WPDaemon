#ifndef SUBMODULE_H
#define SUBMODULE_H

#include <QObject>

class Submodule : public QObject
{
    Q_OBJECT
public:
    explicit Submodule(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SUBMODULE_H