#include "clientinteraction.h"
#include "logincontroller.h"
#include "databasecontroller.h"
ClientInteraction::ClientInteraction(QObject *parent, LoginController *i_login) : QObject(parent), loginController(i_login)
{

}

bool ClientInteraction::login_request(QString username, QString password)
{
return true;
}
