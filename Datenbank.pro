QT += core
QT -= gui

CONFIG += c++11

TARGET = Datenbank
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    database.cpp

HEADERS += \
    database.h
