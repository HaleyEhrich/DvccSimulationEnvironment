QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CXXFLAGS_RELEASE += -OO        # Release -O

SOURCES += \
    configset.cpp \
    functionset.cpp \
    main.cpp \
    mainwindow.cpp \
    paint/aluqgitem.cpp \
    paint/arqgitem.cpp \
    paint/cirgraphicsview.cpp \
    paint/dr1qgitem.cpp \
    paint/dr2qgitem.cpp \
    paint/inputqgitem.cpp \
    paint/irqgitem.cpp \
    paint/microconqgitem.cpp \
    paint/outputqgitem.cpp \
    paint/pcqgitem.cpp \
    paint/r0qgitem.cpp \
    paint/r1qgitem.cpp \
    paint/r2qgitem.cpp \
    paint/ramqgitem.cpp \
    paint/shifter299qgitem.cpp \
    paint/signalsqgitem.cpp \
    systemdataset.cpp \
    toolpannel/componentsettingpannel.cpp \
    toolpannel/logpannel.cpp \
    toolpannel/ramcheck.cpp \
    toolpannel/romcheck.cpp \
    toolpannel/settingpannel.cpp \
    versioninfo.cpp

HEADERS += \
    configset.h \
    functionset.h \
    mainwindow.h \
    paint/aluqgitem.h \
    paint/arqgitem.h \
    paint/cirgraphicsview.h \
    paint/dr1qgitem.h \
    paint/dr2qgitem.h \
    paint/inputqgitem.h \
    paint/irqgitem.h \
    paint/microconqgitem.h \
    paint/outputqgitem.h \
    paint/pcqgitem.h \
    paint/r0qgitem.h \
    paint/r1qgitem.h \
    paint/r2qgitem.h \
    paint/ramqgitem.h \
    paint/shifter299qgitem.h \
    paint/signalsqgitem.h \
    systemdataset.h \
    toolpannel/componentsettingpannel.h \
    toolpannel/logpannel.h \
    toolpannel/ramcheck.h \
    toolpannel/romcheck.h \
    toolpannel/settingpannel.h \
    versioninfo.h

FORMS += \
    mainwindow.ui \
    toolpannel/componentsettingpannel.ui \
    toolpannel/logpannel.ui \
    toolpannel/ramcheck.ui \
    toolpannel/romcheck.ui \
    toolpannel/settingpannel.ui

TRANSLATIONS += \
    DVCC_zh_CN.ts

CONFIG += lrelease

CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/imagine_res/con_img/con_img.qrc \
    resource/imagine_res/icon/icon.qrc \
    resource/imagine_res/img/imgine.qrc \
    resource/imagine_res/menubar/am_menu/am_icon.qrc \
    resource/imagine_res/menubar/file_menu/fm_icon.qrc \
    resource/imagine_res/menubar/om_menu/om_icon.qrc \
    resource/imagine_res/menubar/pm_menu/pm_icon.qrc \
    resource/imagine_res/menubar/rm_menu/rm_icon.qrc \
    resource/imagine_res/window_img/win_img.qrc

RC_ICONS = logo.ico

#DISTFILES +=
