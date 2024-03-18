QT += core
QT -= gui

CONFIG += c++17

TARGET = expressionparser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    pass0.cpp \
    Tokenizer.cpp \
    rpnizer.cpp

HEADERS += \
    defs.h \
    pass0.h \
    Tokenizer.h \
    rpnizer.h \
    interpreter.h \
    utils.h

