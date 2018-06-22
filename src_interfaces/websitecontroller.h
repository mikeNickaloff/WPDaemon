#ifndef WEBSITECONTROLLER_H
#define WEBSITECONTROLLER_H

#include <QObject>
#include <QHash>
class Website;
class DatabaseController;
class WebsiteController : public QObject
{
    Q_OBJECT
public:
    explicit WebsiteController(QObject *parent = nullptr);
    QHash<int, Website*> websites;
    Website* new_website;
    Website* currentWebsite;
signals:

public slots:
};

#endif // WEBSITECONTROLLER_H