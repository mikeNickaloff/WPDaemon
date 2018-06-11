QT -= gui
QT += core network websockets webchannel sql

CONFIG += c++11 console
CONFIG -= app_bundle
WPDaemon.depends = QtWebSocket
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    src_interfaces/clicontroller.cpp \
    src_interfaces/websocketcontroller.cpp \
    src_interfaces/logincontroller.cpp \
    src_websocket/websocketserver.cpp \
    src_interfaces/processcontroller.cpp \
    src_process/processlauncherthread.cpp \
    src_interfaces/clientinteraction.cpp \
    src_wrappers/websocketclientwrapper.cpp \
    src_websocket/websockettransport.cpp \
    src_interfaces/databasecontroller.cpp \
    src_assets/assetunpacker.cpp

HEADERS += \
    src_interfaces/clicontroller.h \
    src_interfaces/websocketcontroller.h \
    src_interfaces/logincontroller.h \
    src_websocket/websocketserver.h \
    src_interfaces/processcontroller.h \
    src_process/processlauncherthread.h \
    src_interfaces/clientinteraction.h \
    src_wrappers/websocketclientwrapper.h \
    src_websocket/websockettransport.h \
    src_interfaces/databasecontroller.h \
    src_assets/assetunpacker.h

RESOURCES += \
    resources.qrc
