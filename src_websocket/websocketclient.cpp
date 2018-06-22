#include "websocketclient.h"
#include "../src_interfaces/clientinteraction.h"
#include "./websockettransport.h"
#include "../src_interfaces/databasecontroller.h"
#include "../src_interfaces/logincontroller.h"
#include "../src_interfaces/firewallcontroller.h"
#include <QWebSocket>
#include <QtDebug>
WebSocketClient::WebSocketClient(QObject *parent, WebSocketTransport* i_client, DatabaseController* i_db, FirewallController *i_firewall) : QObject(parent), m_client(i_client), m_db(i_db), m_firewall(i_firewall)
{
 channel = new QWebChannel(this);
 m_login = new LoginController(this, m_db);
     clientGateway = new ClientInteraction(this, m_login, m_firewall);
     this->connect(clientGateway, &ClientInteraction::LoginFailed, this, &WebSocketClient::process_failed_login);
     channel->registerObject(QStringLiteral("clientInteraction"), clientGateway);
     channel->connectTo(m_client);

     this->remoteIP = m_client->m_socket->peerAddress();
     clientGateway->remoteIP = this->remoteIP.toString();
     if (m_firewall->isBanned(remoteIP.toString())) {
         channel->disconnectFrom(m_client);
         m_client->m_socket->close(QWebSocketProtocol::CloseCodePolicyViolated, "Too many failed Logins - Temporary Ban In place");

     }
     emit clientGateway->requireLogin();
      // qDebug() << "Connection from" << this->remoteIP;

}

void WebSocketClient::process_failed_login()
{
    m_firewall->record_failed_login(this->remoteIP.toString());

}
