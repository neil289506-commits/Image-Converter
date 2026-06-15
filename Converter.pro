QT       += core gui widgets

TARGET = ImageConverter
TEMPLATE = app

# 針對 MSVC 處理 UTF-8
win32-msvc* {
    QMAKE_CXXFLAGS += /utf-8
}

SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h
RESOURCES += resource.qrc
RC_ICONS = images/logo.ico