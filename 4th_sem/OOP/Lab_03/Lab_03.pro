QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configs/configs.cpp \
    drawers/qtdrawer.cpp \
    facade/facade.cpp \
    load/builder.cpp \
    load/loader.cpp \
    main.cpp \
    gui/mainwindow.cpp \
    managers/drawmanager.cpp \
    managers/loadmanager.cpp \
    managers/reformmanager.cpp \
    objects/camera.cpp \
    objects/composite.cpp \
    objects/edge.cpp \
    objects/model.cpp \
    objects/modeldetails.cpp \
    objects/point.cpp \
    scene/scene.cpp \
    visitor/drawvisitor.cpp

HEADERS += \
    commands/command.h \
    configs/configs.h \
    drawers/basedrawer.h \
    drawers/graphsfactory.h \
    drawers/qtdrawer.h \
    errors/errors.h \
    facade/facade.h \
    gui/mainwindow.h \
    load/absloader.h \
    load/builder.h \
    load/loader.h \
    load/modelloader.h \
    managers/basemanager.h \
    managers/drawmanager.h \
    managers/loadmanager.h \
    managers/reformmanager.h \
    objects/camera.h \
    objects/composite.h \
    objects/edge.h \
    objects/model.h \
    objects/modeldetails.h \
    objects/object.h \
    objects/point.h \
    scene/scene.h \
    visitor/drawvisitor.h \
    visitor/visitor.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
