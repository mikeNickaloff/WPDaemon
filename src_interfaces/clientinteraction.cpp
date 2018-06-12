#include "clientinteraction.h"
#include "logincontroller.h"
#include "databasecontroller.h"
#include "firewallcontroller.h"
ClientInteraction::ClientInteraction(QObject *parent, LoginController *i_login, FirewallController* i_firewall) : QObject(parent), loginController(i_login), firewallController(i_firewall)
{

}
/* TO DO
 * - SETUP LOGIN SYSTEM
 * - SETUP SIGNALS/SLOTS FOR HANDLING REQUESTS SECURELY
*/
bool ClientInteraction::login(QString username, QString password)
{
    if (!firewallController->isBanned(this->remoteIP)) {


        if (loginController->loggedIn == false) {
            if (loginController->check_login(username, password) == true) {
                return true;
            }
        } else {

            return true;
        }
    }
    emit this->LoginFailed();
    return false;
}
