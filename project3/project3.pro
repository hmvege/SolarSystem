TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    system.cpp \
    sobject.cpp \
    integrators/integrator.cpp \
    resultstorer.cpp \
    math/vec3.cpp \
    integrators/forwardeuler.cpp

HEADERS += \
    system.h \
    sobject.h \
    integrators/integrator.h \
    resultstorer.h \
    math/vec3.h \
    integrators/forwardeuler.h
