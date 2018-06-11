#include "websocketclient.h"
#include "../src_interfaces/clientinteraction.h"
#include "./websockettransport.h"
#include "../src_interfaces/databasecontroller.h"
#include "../src_interfaces/logincontroller.h"
WebSocketClient::WebSocketClient(QObject *parent, WebSocketTransport* client, DatabaseController* i_db) : QObject(parent), m_db(i_db)
{
 channel = new QWebChannel(this);
 m_login = new LoginController(this, m_db);
     clientGateway = new ClientInteraction(this, m_login);
     channel->registerObject(QStringLiteral("clientInteraction"), clientGateway);
     channel->connectTo(client);

}
