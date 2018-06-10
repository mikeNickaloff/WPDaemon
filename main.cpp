#include <QCoreApplication>
#include "src_interfaces/processcontroller.h"
#include "src_interfaces/websocketcontroller.h"
#include "src_interfaces/clientinteraction.h"
#include "src_assets/assetunpacker.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    AssetUnpacker assets;
    ProcessController processController;
    processController.spawn_internal_process("hello.sh", QStringList());
    WebSocketController ws_c;

    return a.exec();
}
