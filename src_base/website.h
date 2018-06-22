#ifndef WEBSITE_H
#define WEBSITE_H

#include <QObject>

class Website : public QObject
{
    Q_OBJECT
public:
    explicit Website(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WEBSITE_H