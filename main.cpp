#include <QCoreApplication>
#include "src_interfaces/processcontroller.h"
#include "src_interfaces/websocketcontroller.h"
#include "src_interfaces/clientinteraction.h"
#include "src_assets/assetunpacker.h"
#include "src_interfaces/databasecontroller.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    AssetUnpacker assets;
    ProcessController processController;
    processController.spawn_internal_process("start_https.sh", QStringList());
    DatabaseController db_controller;
    WebSocketController ws_controller(0, &db_controller);

    return a.exec();
}
