#-------------------------------------------------
#
# Project created by QtCreator 2017-11-16T02:10:02
#
#-------------------------------------------------

QT       += testlib websockets

QT       -= gui

TARGET = tst_sysinfotest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += tst_sysinfotest.cpp \
    ../sysinfoserver/configuration.cpp \
    ../sysinfoserver/database.cpp \
    ../sysinfoserver/sendmail.cpp \
    ../sysinfoserver/sysinfoserver.cpp \
    ../sysinfoclient/sysinfo.cpp \
    ../sysinfoclient/sysinfoclient.cpp \
    ../sysinfo_api/exception.cpp \
    ../sysinfo_api/packet.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../sysinfoserver/configuration.h \
    ../sysinfoserver/database.h \
    ../sysinfoserver/sendmail.h \
    ../sysinfoserver/sysinfoserver.h \
    ../sysinfoclient/sysinfo.h \
    ../sysinfoclient/sysinfoclient.h \
    ../sysinfo_api/exception.h \
    ../sysinfo_api/log.h \
    ../sysinfo_api/packet.h
