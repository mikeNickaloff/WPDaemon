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
        rv = QString("<input type='text' name='%1' class='w3-input w3-rest w3-border-red wp-parameter' required>").arg(parameterIndex);
    }
    if (isOptional) {
        rv = QString("<input type='text' name='%1' class='w3-input w3-rest w3-border-blue wp-parameter'>").arg(parameterIndex);
    }
    if (isSwitch) {
        rv = QString("<input type='checkbox' name='%1' class='w3-checkbox w3-rest w3-large wp-parameter'>").arg(parameterIndex);
    }
    if (isLong) {
        flagValue.remove("&");
        flagValue.remove(">");
        flagValue.remove("<");
        flagValue.remove("--");
        flagValue.remove("\"");
        flagValue.remove("[");
        flagValue.remove("]");
        flagValue.remove("}");
        flagValue.remove("{");
        flagValue.remove("\\n");
        flagValue.remove(" ");
        flagValue.remove(QChar(QChar::LineFeed));
        flagValue.remove(QChar(QChar::CarriageReturn));
        flagValue.remove(QChar(QChar::LineSeparator));

        rv = QString("<input type='text' name='%1' class=' w3-input w3-rest w3-large wp-parameter' placeholder='%2'>").arg(parameterIndex).arg(flagValue);
    }

    return rv;

}

QString CommandParameter::toString()
{
    QString rv;
    if ((isOptional == true) || (isRequired == true)) {

        return this->parameterValue.toString();

    }
    if (isSwitch == true) {
        if (this->parameterValue.toBool() == true) {
            return QString("--%1").arg(this->flagProperty);
        } else {
            return " ";
        }
    }
    if (isLong == true) {
        if (parameterValue.toString().length() > 0) {
            return QString("--%1=%2").arg(flagProperty).arg(parameterValue.toString());
        } else {
            return "";
        }
    }

    return " ";
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
                flagProperty = m_string;
                if (flagProperty.length() > 2) {
                    flagProperty.remove(0, 3);
                }


            } else {
                // qDebug() << "optional" << optional.first();
                isOptional = true;
                m_string = optional.first();
                flagProperty = "";
            }
        } else {
            // qDebug() << "requiured" << required.first();
            isRequired = true;
            m_string = required.first();
            flagProperty = "";
        }
    } else {
        // qDebug() << "optional flag" << optionalFlags.first();
        m_string = optionalFlags.first();
        flagProperty = m_string.split("=").first();
        if (flagProperty.length() > 3) {
            flagProperty.remove(0, 3);
        }
        flagValue = m_string.split("=").last();
        isLong = true;
    }

}

void CommandParameter::set_value(QVariant val)
{
    this->parameterValue = val;
}
