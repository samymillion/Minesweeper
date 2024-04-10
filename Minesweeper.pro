# Project Name
TARGET = Minesweeper

# Project version
VERSION = 1.0.0

# Configuration
CONFIG += c++11
CONFIG += qt
QT += widgets

# Define the sources and headers
SOURCES += main.cpp \
           MainWindow.cpp \
           MineButton.cpp \
           GameLogic.cpp

HEADERS += MainWindow.h \
           MineButton.h \
           GameLogic.h


# Define resources
RESOURCES += MyRes.qrc


# Installation path
# target.path = /path/to/installation
# INSTALLS += target
