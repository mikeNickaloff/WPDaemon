#include "logincontroller.h"
#include "databasecontroller.h"
LoginController::LoginController(QObject *parent, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{

}
