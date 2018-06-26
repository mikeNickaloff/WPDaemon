#ifndef COMMANDPARAMETER_H
#define COMMANDPARAMETER_H

#include <QObject>
#include <QVariant>
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
    bool isSwitch;
    int parameterIndex;
    QString m_string;
    QStringList find_captures(QString regexString);

    QString html();
    QString flagProperty;
    QString flagValue;
    QVariant parameterValue;
    QString toString();
signals:

public slots:
void parse();
void set_value(QVariant val);

};

#endif // COMMANDPARAMETER_H