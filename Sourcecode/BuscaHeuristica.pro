TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
#QMAKE_CXXFLAGS += -O5

INCLUDEPATH += \
    ./headers \
    ./sources

SOURCES += \
    sources/principal.cpp \
    sources/buscaheuristica.cpp \
    sources/primeiramelhora.cpp \
    sources/tabu.cpp \
    sources/maquina.cpp \
    sources/tarefa.cpp

HEADERS += \
    headers/buscaheuristica.h \
    headers/primeiramelhora.h \
    headers/tabu.h \
    headers/maquina.h \
    headers/tarefa.h
