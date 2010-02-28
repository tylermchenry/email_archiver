TEMPLATE = app
TARGET = email_archiver
QT += core \
    gui \
    sql \
    network
HEADERS += src/archiver.h
SOURCES += src/archiver.cpp \
    src/main.cpp
FORMS += src/archiver.ui
RESOURCES += 
