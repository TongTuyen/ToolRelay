#-------------------------------------------------
#
# Project created by QtCreator 2018-04-03T09:38:15
#
#-------------------------------------------------

QT       += core gui serialport

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RELAYTOLL
TEMPLATE = app


SOURCES += main.cpp\
        Devicemanager.cpp \
    imodbusdevice.cpp \
    clsrelay.cpp \
    crcmodbus.cpp \
    QRingBuffer.cpp \
    clscoil.cpp

HEADERS  += Devicemanager.h \
    imodbusdevice.h \
    clsrelay.h \
    crcmodbus.h \
    QRingBuffer.h \
    typedefs.h \
    clscoil.h

FORMS    += mainwindow.ui
