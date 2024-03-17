QT += core
QT -= gui

CONFIG += c++17

TARGET = expressionparser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Tokenizer.cpp \
    ast.cpp \
    rpnizer.cpp

HEADERS += \
    Tokenizer.h \
    ast.h \
    defs.h \
    interpreter.h \
    rpnizer.h \
    utils.h

