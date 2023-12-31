QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    interface/mainwindow.cpp \
    logic/edges/edge.cpp \
    logic/edges/edges.cpp \
    logic/model/manager.cpp \
    logic/model/model3D.cpp \
    logic/points/point2D/point2D.cpp \
    logic/points/point2D/points2D.cpp \
    logic/points/point3D/point3D.cpp \
    logic/points/point3D/points3D.cpp \
    logic/scene/scene_init.cpp \
    main.cpp

HEADERS += \
    interface/mainwindow.h \
    logic/edges/edge.h \
    logic/edges/edges.h \
    logic/model/errors.h \
    logic/model/manager.h \
    logic/model/model2D.h \
    logic/model/model3D.h \
    logic/model/model_params.h \
    logic/points/point2D/point2D.h \
    logic/points/point2D/points2D.h \
    logic/points/point3D/point3D.h \
    logic/points/point3D/points3D.h \
    logic/scene/scene.h \
    logic/scene/scene_init.h \
    logic/scene/screen.h

FORMS += \
    interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
