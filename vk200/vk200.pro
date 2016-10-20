#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T17:16:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = vk200
TEMPLATE = app


SOURCES += main.cpp\
        vk.cpp

HEADERS  += vk.h \
    user.h \
    debug.h \
    message.h \
    includes.h

FORMS    += vk.ui

QMAKE_CXX = clang++
QMAKE_INCDIR += /usr/include/c++/6.1.1/x86_64-pc-linux-gnu
QMAKE_CXXFLAGS += -std=c++14
