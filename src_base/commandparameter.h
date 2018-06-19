#ifndef COMMANDPARAMETER_H
#define COMMANDPARAMETER_H

#include <QObject>

class CommandParameter : public QObject
{
    Q_OBJECT
public:
    explicit CommandParameter(QObject *parent = nullptr, QString i_argString = "" );
    bool isRequired;
    bool isOptional;
    bool isLong;
    bool hasDefaultValue;
    bool isVarArg;
    QString m_string;
    QStringList find_captures(QString regexString);
signals:

public slots:
void parse();

};

#endif // COMMANDPARAMETER_H