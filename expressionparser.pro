QT += core
QT -= gui

CONFIG += c++11

TARGET = expressionparser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp  \
    kars.cpp

HEADERS += \
    defs.h \
    kars.h \
    pass1.h

