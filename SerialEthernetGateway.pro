QT -= gui
QT += network serialport

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QESP_NO_UDEV
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    connection.cpp \
    3rd/qextserialport/src/qextserialenumerator_linux.cpp \
    3rd/qextserialport/src/qextserialenumerator.cpp \
    3rd/qextserialport/src/qextserialport.cpp \
    3rd/qextserialport/src/qextserialport_unix.cpp

HEADERS += \
    connection.h \
    3rd/qextserialport/src/qextserialenumerator_p.h \
    3rd/qextserialport/src/qextserialenumerator.h \
    3rd/qextserialport/src/qextserialport_global.h \
    3rd/qextserialport/src/qextserialport_p.h \
    3rd/qextserialport/src/qextserialport.h
