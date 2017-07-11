TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    priorityqueue.cpp \
    chores.cpp

HEADERS += \
    chores.h \
    priorityqueue.h
