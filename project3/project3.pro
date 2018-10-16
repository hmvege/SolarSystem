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
    integrators/forwardeuler.cpp \
    force/force.cpp \
    force/newtoniangravity.cpp \
    integrators/velocityverlet.cpp

HEADERS += \
    system.h \
    sobject.h \
    integrators/integrator.h \
    resultstorer.h \
    math/vec3.h \
    integrators/forwardeuler.h \
    force/force.h \
    force/newtoniangravity.h \
    integrators/velocityverlet.h
