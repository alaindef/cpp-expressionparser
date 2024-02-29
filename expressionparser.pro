QT += core
QT -= gui

CONFIG += c++11

TARGET = expressionparser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    defs.h \
    pass1.h \
    pass2.h \
    utils.h

