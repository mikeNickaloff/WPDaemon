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
    explicit WebsiteController(QObject *parent = nullptr, DatabaseController* i_db = nullptr);
    //  to be implemented if expanding later
  //QHash<int, Website*> websites;
  //  Website* new_website;
 //   Website* currentWebsite;

  QString currentWebsite;
  QHash<QString, QString> websites;


    DatabaseController* db;
signals:

public slots:
    void add_site(QString i_name, QString i_path);
};

#endif // WEBSITECONTROLLER_H
