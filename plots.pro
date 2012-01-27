TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp

LIBS += -lgrace_np

QMAKE_CXXFLAGS += -std=c++0x
QMAKE_DEBUG_CXXFLAGS += -std=c++0x
