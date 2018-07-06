#include "clientinteraction.h"
#include "logincontroller.h"
#include "databasecontroller.h"
#include "firewallcontroller.h"
#include "../src_base/submodule.h"
#include "../src_base/submodulecommand.h"
#include "../src_base/commandparameter.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVariantHash>
#include <QVariant>
#include <QtDebug>
#include "../src_interfaces/processcontroller.h"
#include "../src_process/processlauncherthread.h"
#include "websitecontroller.h"
#include <QDir>
ClientInteraction::ClientInteraction(QObject *parent, LoginController *i_login, FirewallController* i_firewall, DatabaseController *i_db) : QObject(parent), loginController(i_login), firewallController(i_firewall), db(i_db)
{
 this->websiteController = new WebsiteController(this, db);
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
                  //  // qDebug() << obj << rv;
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
              /*QString syn = currentSubmodule->get_command_dump("synopsis").toString();
               QStringList synList = syn.split("\n", QString::KeepEmptyParts); */

              QString rv = "{\"commands\":[";
              //if (synList.count() != descList.count()) {  // qDebug() << "Synopsis Size Mismatch"; } else {

              for (int i=0; i<nameList.count(); i++) {
                  if (descList.count() > i) {
                      QString newStr = QString("{\"name\":%1,\"description\":%2}").arg(nameList.at(i)).arg(descList.at(i));
                      if ((descList.count() - 1) != i) {
                          newStr.append(",");
                          QString syn = this->currentSubmodule->get_synopsis("synopsis", i).toString();
                          // if (synList.count() > i) {
                          this->currentSubmodule->add_command(nameList.at(i), descList.at(i), syn);
                          //  }


                        }
                      rv.append(newStr);
                    }
                }
              rv.append("]}");
              // // qDebug() << arrList.count();


              return QVariant::fromValue(rv);

            }
        }

    } else {
      return QVariant::fromValue(QString("{}"));
    }
  return QVariant::fromValue(QString("{}"));
}

QVariant ClientInteraction::set_current_command(QString i_command)
{
  if (this->currentSubmodule != nullptr) {
      int opResult = currentSubmodule->set_current_command(i_command);
      //    // qDebug() << "operation result" << opResult;
      if (opResult != -1) {
          // command exists as part of current submodule
          QString rv = "{\"parameters\":[";
          this->currentSubmodule->currentCommand->init_parameters();

          for (int i=0; i<this->currentSubmodule->currentCommand->parameters.values().count(); i++) {
              CommandParameter* param = this->currentSubmodule->currentCommand->parameters[i];
              QString paramType = "none";
              if (param->isRequired == true) {
                  paramType = "required";
                }
              if (param->isOptional == true) {
                  paramType = "optional";
                }
              if (param->isSwitch == true) {
                  paramType = "switch";
                }
              if (param->isLong == true) {
                  paramType = "long";
                }
              param->m_string.remove("&");
              param->m_string.remove(">");
              param->m_string.remove("<");
              param->m_string.remove("--");
              param->m_string.remove("\"");
              param->m_string.remove("[");
              param->m_string.remove("]");
              param->m_string.remove("}");
              param->m_string.remove("{");
              param->m_string.remove("\\n");
              param->m_string.remove(QChar(QChar::LineFeed));
              param->m_string.remove(QChar(QChar::CarriageReturn));
              param->m_string.remove(QChar(QChar::LineSeparator));
              if ((param->isRequired) || (param->isOptional)) {
                  QString newStr = QString("{\"name\":\"%1\",\"type\":\"%2\",\"html\":\"%3\"}").arg(param->m_string).arg(paramType).arg(param->html());
                  rv.append(newStr);
                }
              if ((param->isSwitch) || (param->isLong) || (param->isRequiredLong)) {

                  param->flagProperty.remove("&");
                  param->flagProperty.remove(">");
                  param->flagProperty.remove("<");
                  param->flagProperty.remove("--");
                  param->flagProperty.remove("\"");
                  param->flagProperty.remove("[");
                  param->flagProperty.remove("]");
                  param->flagProperty.remove("}");
                  param->flagProperty.remove("{");
                  param->flagProperty.remove("\\n");
                  param->flagProperty.remove(" ");
                  param->flagProperty.remove(QChar(QChar::LineFeed));
                  param->flagProperty.remove(QChar(QChar::CarriageReturn));
                  param->flagProperty.remove(QChar(QChar::LineSeparator));


                  QString newStr = QString("{\"name\":\"%1\",\"type\":\"%2\",\"html\":\"%3\"}").arg(param->flagProperty).arg(paramType).arg(param->html());
                  rv.append(newStr);
                }
              if (i < (this->currentSubmodule->currentCommand->parameters.values().count() - 1)) {
                  rv.append(",");
                }
            }
          rv.append("]}");
          // qDebug() << rv;
          return QVariant::fromValue(rv);
        } else {
          // command doesnt exist.
          // qDebug() << "No such command";
          return QVariant::fromValue(QString("{\"parameters\":[]}"));
        }


    } else {
      // qDebug() << "No submodule selected";
      // current submodule not selected.
      //  return empty array
      return QVariant::fromValue(QString("{}"));
    }
}

QVariant ClientInteraction::execute()
{
  QString rv;
  if (this->currentSubmodule != nullptr) {
      rv.append(currentSubmodule->toString());
    }
  if (websiteController->currentWebsite == "./tmp") { return QVariant::fromValue(QString("Error. please select a website to execute command for")); }
  this->processLauncher = new ProcessLauncherThread("wp", (QStringList() << rv.split(" ", QString::SkipEmptyParts)), "internal");
  QByteArray output;
  output.append(processLauncher->run_internal_script("wp", (QStringList() << QString("--path=%1").arg(websiteController->currentWebsite) << rv.split(" ", QString::SkipEmptyParts))));

   qDebug() << output;
  return QVariant::fromValue(output);

  //return QVariant::fromValue(rv);
}

QVariant ClientInteraction::add_site(QString i_name, QString i_path)
{
  if (loginController->loggedIn == true) {
      QDir dir(i_path);
      if (dir.exists()) {
          if (dir.isReadable()) {

              websiteController->add_site(i_name, i_path);
              return "Success";
            } else {
              return QString("No permission to access the path %1").arg(dir.canonicalPath());
            }
        } else {
          bool ok = QDir("/").mkpath(i_path);
          if (!ok) {
              return QString("No permission to create the path %1").arg(dir.canonicalPath());
            }
        }
    }
  return "Fail";
}

QVariant ClientInteraction::websites()
{
  if (!loginController->loggedIn) { emit this->requireLogin(); return QVariant::fromValue(QString("")); } else {
      QVariantList rv;
      QJsonDocument doc;
      QJsonArray main_array;
      QHash<QString, QString>::const_iterator i = websiteController->websites.constBegin();

      while (i != websiteController->websites.constEnd()) {

          QVariantHash hash;
          hash["sitename"] = i.key();
          hash["sitepath"] = i.value();
          QJsonObject obj = QJsonObject::fromVariantHash(hash);
          rv.append(obj);
          //  // qDebug() << obj << rv;



      i++;
    }
  main_array = QJsonArray::fromVariantList(rv);

  QJsonObject mainObject;


  mainObject.insert("websites", QJsonValue::fromVariant(rv));
  doc.setObject(mainObject);

  return QVariant::fromValue(doc.toJson(QJsonDocument::Compact));
}
}

void ClientInteraction::set_parameter_value(int paramidx, QVariant val)
{
  if (this->currentSubmodule != nullptr) {
      if (this->currentSubmodule->currentCommand != nullptr) {
          if (this->currentSubmodule->currentCommand->parameters.keys().contains(paramidx)) {
              CommandParameter* param = currentSubmodule->currentCommand->parameters[paramidx];
              param->set_value(val);
            }
        }
    }
}

bool ClientInteraction::set_current_site(QString sitename)
{
  if( websiteController->websites.keys().contains(sitename)) {
      this->websiteController->currentWebsite = websiteController->websites.value(sitename);
      return true;
    } else {
      this->websiteController->currentWebsite = websiteController->websites.value("./tmp");
      return false;
    }
  return false;
}
