INCLUDEPATH += "C:\\Program Files (x86)\\FMOD SoundSystem\\FMOD Programmers API Win32\\api\\inc"
LIBS += -lfmodex

QT+=widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    aboutlightcontroller.cpp \
    serialport.cpp \
    fixtures.cpp \
    groups.cpp \
    scenes.cpp \
    faders.cpp \
    timing.cpp

FORMS += \
    mainwindow.ui \
    aboutlightcontroller.ui \
    serialport.ui \
    fixtures.ui \
    groups.ui \
    scenes.ui \
    faders.ui \
    timing.ui

HEADERS += \
    mainwindow.h \
    aboutlightcontroller.h \
    serialport.h \
    fixtures.h \
    groups.h \
    scenes.h \
    faders.h \
    timing.h

RESOURCES += \
    Ressources.qrc
