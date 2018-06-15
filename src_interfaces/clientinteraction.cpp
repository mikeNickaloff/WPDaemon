#include "clientinteraction.h"
#include "logincontroller.h"
#include "databasecontroller.h"
#include "firewallcontroller.h"
#include "../src_base/submodule.h"
#include "../src_base/submodulecommand.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantHash>
#include <QVariant>
#include <QtDebug>
ClientInteraction::ClientInteraction(QObject *parent, LoginController *i_login, FirewallController* i_firewall) : QObject(parent), loginController(i_login), firewallController(i_firewall)
{

}

bool ClientInteraction::login(QString username, QString password)
{
    if (!firewallController->isBanned(this->remoteIP)) {


        if (loginController->loggedIn == false) {
            if (loginController->check_login(username, password) == true) {
                emit this->LoginSuccessful();
                return true;
            }
        } else {

            return true;
        }
    }
    emit this->LoginFailed();
    return false;
}

QVariant ClientInteraction::allowedSubmodules()
{
    if (!loginController->loggedIn) { emit this->requireLogin(); return QVariant::fromValue(QString("")); } else {
    QVariantList rv;
    QJsonDocument doc;
    QJsonArray main_array;
    QHash<int, bool>::const_iterator i = loginController->assignments.constBegin();
    QList<int> assignmentNameKeys;
    QList<int> assignmentDescriptionKeys;
    assignmentDescriptionKeys << loginController->assignment_descriptions.keys();
    assignmentNameKeys << loginController->assignment_names.keys();
    while (i != loginController->assignments.constEnd()) {
        bool isEnabled = i.value();
        int assignmentId = i.key();
        if (isEnabled) {
            if ((assignmentNameKeys.contains(assignmentId)) && (assignmentDescriptionKeys.contains(assignmentId))) {
                //QString mergedString = QString("%1!!!%2").arg(loginController->assignment_names[assignmentId]).arg(loginController->assignment_descriptions[assignmentId]);
                //rv << mergedString;
                QVariantHash hash;
                hash["name"] = loginController->assignment_names[assignmentId];
                hash["description"] = loginController->assignment_descriptions[assignmentId];
                QJsonObject obj = QJsonObject::fromVariantHash(hash);
                rv.append(obj);
               // qDebug() << obj << rv;
            }
        }

        i++;
    }
    main_array = QJsonArray::fromVariantList(rv);

    QJsonObject mainObject;


    mainObject.insert("submodules", QJsonValue::fromVariant(rv));
    doc.setObject(mainObject);

    return QVariant::fromValue(doc.toJson(QJsonDocument::Compact));
    }
}

QVariant ClientInteraction::set_current_submodule(QString i_module)
{

    if (loginController->assignment_id_names.keys().contains(i_module)) {
        int tmpId = loginController->assignment_id_names[i_module];
        if (loginController->assignments.keys().contains(tmpId)) {
            if (this->loginController->assignments[tmpId] == true) {
               currentSubmodule = new Submodule(this);
               currentSubmodule->moduleName = i_module;
               QString names = currentSubmodule->get_command_dump("name").toString();
               QStringList nameList = names.split("\n", QString::SkipEmptyParts);
               QString desc = currentSubmodule->get_command_dump("description").toString();
               QStringList descList = desc.split("\n", QString::SkipEmptyParts);
               QString syn = currentSubmodule->get_command_dump("synopsis").toString();
               QStringList synList = syn.split("\n", QString::SkipEmptyParts);
               QString rv = "{\"commands\":[";

               for (int i=0; i<nameList.count(); i++) {
                   if (descList.count() > i) {
                       QString newStr = QString("{\"name\":%1,\"description\":%2}").arg(nameList.at(i)).arg(descList.at(i));
                       if ((descList.count() - 1) != i) {
                           newStr.append(",");
                       }
                       rv.append(newStr);
                   }
               }
               rv.append("]}");
               //qDebug() << arrList.count();


               return QVariant::fromValue(rv);

            }
        }

    } else {
        return QVariant::fromValue(QString("{}"));
    }
    return QVariant::fromValue(QString("{}"));
}
