#include "commandparameter.h"
#include <QRegExp>
#include <QtDebug>

CommandParameter::CommandParameter(QObject *parent, QString i_argString) : QObject(parent), m_string(i_argString)
{
    isRequired = false;
    isOptional = false;
    isLong = false;
    isVarArg = false;
    isSwitch = false;
    parse();
}

QStringList CommandParameter::find_captures(QString regexString)
{
    QRegExp rx(regexString);

    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(m_string, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    return list;
}

QString CommandParameter::html()
{
    QString rv;
    if (isRequired) {
        rv = QString("<input type='text' name='%1' class='w3-input w3-rest w3-border-red' required>").arg(parameterIndex);
    }
    if (isOptional) {
        rv = QString("<input type='text' name='%1' class='w3-input w3-rest w3-border-blue'>").arg(parameterIndex);
    }

    return rv;

}

void CommandParameter::parse()
{
    QStringList optionalFlags;
    optionalFlags << this->find_captures("(\\[\\-\\-\\S+\\=<\\S+\\>\\]\\B)");
    if (optionalFlags.count() == 0) {
        QStringList required;

        required << this->find_captures("(\\<\\S+\\>\\B)");
        if (required.count() == 0) {
            QStringList optional;
            optional << this->find_captures("(\\[\\[^\\>\\<]+\\]\\B)");
            if (optional.count() == 0) {
                 // qDebug() << "Switch" << m_string;
                isSwitch = true;

            } else {
                 // qDebug() << "optional" << optional.first();
                isOptional = true;
                m_string = optional.first();
            }
        } else {
             // qDebug() << "requiured" << required.first();
            isRequired = true;
            m_string = required.first();
        }
    } else {
         // qDebug() << "optional flag" << optionalFlags.first();
        m_string = optionalFlags.first();
        isLong = true;
    }

}
