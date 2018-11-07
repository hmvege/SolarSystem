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
    force/modifiedgravity.cpp \
    force/newtoniangravitycorrected.cpp \
    integrators/velocityverlet.cpp \
    integrators/eulercromer.cpp \


HEADERS += \
    system.h \
    sobject.h \
    integrators/integrator.h \
    resultstorer.h \
    math/vec3.h \
    integrators/forwardeuler.h \
    force/force.h \
    force/newtoniangravity.h \
    force/modifiedgravity.h \
    force/newtoniangravitycorrected.h \
    integrators/velocityverlet.h \
    integrators/eulercromer.h \


# Adds processor specific optimizations
QMAKE_CFLAGS += -march=native
QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS_RELEASE += -march=native

# Adds O3 optimizations
QMAKE_CFLAGS += -O3
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS_RELEASE += -O3

# Forces C++11
QMAKE_CFLAGS += -std=c++11
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE += -std=c++11

# Removes flags
QMAKE_CFLAGS -= -O2
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
