QT += core
QT -= gui

CONFIG += c++17

TARGET = expressionparser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Tokenizer.cpp \
    pass2.cpp

HEADERS += \
    Tokenizer.h \
    defs.h \
    interpreter.h \
    pass2.h \
    utils.h

