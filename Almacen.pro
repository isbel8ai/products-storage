#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T21:51:40
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Almacen
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    warehouse.cpp \
    inputdialog.cpp \
    outputdialog.cpp \
    productmanager.cpp \
    productadddialog.cpp \
    productupdatedialog.cpp \
    storemanager.cpp \
    storeadddialog.cpp \
    storeupdatedialog.cpp \
    storehouse.cpp

HEADERS  += mainwindow.h \
    warehouse.h \
    inputdialog.h \
    outputdialog.h \
    productmanager.h \
    productadddialog.h \
    productupdatedialog.h \
    storemanager.h \
    storeadddialog.h \
    storeupdatedialog.h \
    storehouse.h

FORMS    += mainwindow.ui \
    warehouse.ui \
    inputdialog.ui \
    outputdialog.ui \
    productmanager.ui \
    productadddialog.ui \
    productupdatedialog.ui \
    storemanager.ui \
    storeadddialog.ui \
    storeupdatedialog.ui \
    storehouse.ui

RESOURCES += \
    utils.qrc
