QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp

HEADERS += \
    authorizationwindow.h \
    emailconfirmwindow.h \
    enteringwindow.h \
    interactionwindow.h \
    profilewindow.h \
    registrationwindow.h \
    smtp.h

FORMS += \
    authorization.ui \
    emailconfirm.ui \
    entering.ui \
    interaction.ui \
    profile.ui \
    registration.ui

RC_FILE = logo.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    logo.qrc

win32: LIBS += -L$$PWD/../../opencv/install/x64/mingw/lib/ \
    -lopencv_highgui490 \
    -lopencv_core490 \
    -lopencv_imgcodecs490 \
    -lopencv_videoio490 \
    -lopencv_imgproc490 \
    -lopencv_objdetect490 \
    -lopencv_features2d490 \
    -lopencv_calib3d490

INCLUDEPATH += $$PWD/../../opencv/install/include
DEPENDPATH += $$PWD/../../opencv/install/include

DISTFILES += \
    logo.rc

