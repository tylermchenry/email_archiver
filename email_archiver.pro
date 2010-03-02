TEMPLATE = app
TARGET = email_archiver
QT += core \
    gui \
    sql \
    network
HEADERS += src/messagemodel.h \
    src/mailmessage.h \
    src/mboximporter.h \
    src/archiver.h
SOURCES += src/messagemodel.cpp \
    src/mailmessage.cpp \
    src/mboximporter.cpp \
    src/archiver.cpp \
    src/main.cpp
FORMS += src/archiver.ui
RESOURCES += 
