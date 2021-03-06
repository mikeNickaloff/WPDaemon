#include "submodulecommand.h"
#include "commandparameter.h"
#include <QtDebug>
SubmoduleCommand::SubmoduleCommand(QObject *parent,  QString i_name, QString i_description,QString i_synopsis) : QObject(parent), name(i_name), description(i_description), synopsis(i_synopsis)
{
    init_parameters();
}

QString SubmoduleCommand::toString()
{
    QString rv = " ";
    rv.append(name);
    rv.append(" ");
 for (int i=0; i<this->parameters.values().count(); i++) {
     rv.append(" ");
     rv.append(parameters[i]->toString());
     rv.append(" ");
 }
 return rv;
}

void SubmoduleCommand::init_parameters()
{
    this->parameters.clear();
    QStringList synParams;
    synParams << this->synopsis.split(" ",  QString::SkipEmptyParts);
     // qDebug() << synParams;
    for (int i=0; i<synParams.count(); i++) {
        QString tmp_str = synParams.at(i);
        newParameter = new CommandParameter(this, tmp_str);
        //newParameter->parse();
        newParameter->parameterIndex = i;
        this->parameters[i] = newParameter;
    }
}
