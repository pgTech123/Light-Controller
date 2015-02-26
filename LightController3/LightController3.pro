#INCLUDEPATH += "C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Programmers API Win32\\api\\inc"
#LIBS += -lfmodex

QT+=widgets

SOURCES += \
    main.cpp \
    rs232win.cpp \
    rs232linux.cpp \
    Widgets/aboutlightcontroller.cpp \
    Widgets/dockablewindow.cpp \
    Widgets/faders.cpp \
    Widgets/fixtures.cpp \
    Widgets/groups.cpp \
    Widgets/mainwindow.cpp \
    Widgets/scenes.cpp \
    Widgets/serialport.cpp \
    Widgets/timing.cpp \
    History/localhistory.cpp \
    History/history.cpp \
    lightsavailable.cpp \
    Widgets/groupediting.cpp

FORMS += \
    Widgets/mainwindow.ui \
    Widgets/aboutlightcontroller.ui \
    Widgets/serialport.ui \
    Widgets/fixtures.ui \
    Widgets/groups.ui \
    Widgets/scenes.ui \
    Widgets/faders.ui \
    Widgets/timing.ui \
    Widgets/groupediting.ui

HEADERS += \
    rs232win.h \
    rs232linux.h \
    Widgets/aboutlightcontroller.h \
    Widgets/dockablewindow.h \
    Widgets/faders.h \
    Widgets/fixtures.h \
    Widgets/groups.h \
    Widgets/mainwindow.h \
    Widgets/scenes.h \
    Widgets/serialport.h \
    Widgets/timing.h \
    History/localhistory.h \
    History/history.h \
    lightsavailable.h \
    Widgets/groupediting.h
