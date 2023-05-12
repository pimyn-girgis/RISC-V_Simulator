QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeeditor.cpp \
    filebuttonmenu.cpp \
    highlighter.cpp \
    main.cpp \
    mainwin.cpp \
    mapmodel.cpp \
    risc_srcs/genUtils.cpp \
    risc_srcs/memory.cpp \
    risc_srcs/riscv.cpp \
    topbarwidget.cpp

HEADERS += \
    codeeditor.h \
    filebuttonmenu.h \
    highlighter.h \
    mainwin.h \
    mapmodel.h \
    risc_srcs/genUtils.h \
    risc_srcs/memory.h \
    risc_srcs/riscv.h \
    topbarwidget.h

FORMS += \
    filebuttonmenu.ui \
    mainwin.ui

win32{
	SOURCES +=
}
macx{
    OBJECTIVE_SOURCES += \
		framelesswindow.mm
    LIBS += -framework Cocoa
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resources/RAWRS.png

RESOURCES += \
    resources.qrc
