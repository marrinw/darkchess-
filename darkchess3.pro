QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ConnectedServer.cpp\
    assForAgent.cpp\
    clientagentB.cpp\
    main.cpp\
    mainwindow.cpp\
    chessman.cpp\
    chesslabel.cpp\
    chessboard.cpp\
    pvp.cpp\
    agent.cpp\
    agentvsagent.cpp\
    netserver.cpp\
    netclient.cpp\
    serveragent.cpp\
    clientagent.cpp
HEADERS += \
    ConnectedServer.h\
    assForAgent.h\
    clientagentB.h\
    mainwindow.h\
    chessman.h\
    chesslabel.h\
    chessboard.h\
    pvp.h\
    agent.h\
    agentvsagent.h\
    netserver.h\
    netclient.h\
    serveragent.h\
    clientagent.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
