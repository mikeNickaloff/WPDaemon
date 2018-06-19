#include "commandparameter.h"
#include <QRegExp>
#include <QtDebug>

CommandParameter::CommandParameter(QObject *parent, QString i_argString) : QObject(parent), m_string(i_argString)
{

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

void CommandParameter::parse()
{
  qDebug() << this->find_captures("(\\<\\S+\\>\\B)");
  qDebug() << this->find_captures("(\\[\\S+\\]\\B)");
  qDebug() << this->find_captures("(\\[\\S+\\=<\\S+\\>\\]\\B)");
}
