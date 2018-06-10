#include <QCoreApplication>
#include "src_interfaces/processcontroller.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ProcessController processController;
    processController.spawn_internal_process("hello.sh", QStringList());
    return a.exec();
}
