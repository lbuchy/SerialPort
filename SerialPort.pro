TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    serialport.cpp

unix:!macx: LIBS += -lboost_thread-mt -lboost_system-mt -lboost_signals-mt -lpthread

HEADERS += \
    serialport.h

OTHER_FILES +=
