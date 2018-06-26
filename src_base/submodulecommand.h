#ifndef SUBMODULECOMMAND_H
#define SUBMODULECOMMAND_H

#include <QObject>
#include <QHash>
class CommandParameter;
class SubmoduleCommand : public QObject
{
    Q_OBJECT
public:
    explicit SubmoduleCommand(QObject *parent = nullptr, QString i_name = "", QString i_description = "",QString i_synospsis = "");
    QString name;
    QString description;
    QString synopsis;
    QHash<int, CommandParameter*> parameters;
    CommandParameter* newParameter;
    QString toString();
signals:

public slots:
    void init_parameters();

};

#endif // SUBMODULECOMMAND_H