#include "logincontroller.h"
#include "databasecontroller.h"
LoginController::LoginController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{
    this->hello_str = "hello, world!";
    loggedIn = false;
}

bool LoginController::check_login(QString username, QString password)
{
    if ((username == "asdf") && (password == "none")) {
        loggedIn = true;
        return true;
    }
    loggedIn = false;
    return false;
}

void LoginController::hello()
{

}
