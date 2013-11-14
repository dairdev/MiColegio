#-------------------------------------------------
#
# Project created by QtCreator 2012-11-25T19:35:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MiColegio
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    frmalumnos.cpp \
    frmproductos.cpp \
    producto.cpp \
    genderitemdelegate.cpp \
    gendercelldelegate.cpp \
    frmsysoptions.cpp \
    frmcategoria.cpp \
    dlglogin.cpp \
    myapplication.cpp \
    frmalumno.cpp \
    auditoria.cpp \
    frmventas.cpp \
    frmcompras.cpp

HEADERS  += mainwindow.h \
    frmalumnos.h \
    initdb.h \
    frmproductos.h \
    producto.h \
    genderitemdelegate.h \
    gendercelldelegate.h \
    frmsysoptions.h \
    frmcategoria.h \
    dlglogin.h \
    myapplication.h \
    frmalumno.h \
    auditoria.h \
    frmventas.h \
    frmcompras.h

FORMS    += mainwindow.ui \
    frmalumnos.ui \
    frmproductos.ui \
    producto.ui \
    frmsysoptions.ui \
    frmcategoria.ui \
    dlglogin.ui \
    frmalumno.ui \
    frmventas.ui \
    frmcompras.ui

RESOURCES += \
    micolegio.qrc
