TEMPLATE = app
TARGET = email_archiver
QT += core \
    gui \
    sql \
    network
HEADERS += src/mboximporter.h \
    src/archiver.h
SOURCES += src/mboximporter.cpp \
    src/archiver.cpp \
    src/main.cpp
FORMS += src/archiver.ui
RESOURCES += 
