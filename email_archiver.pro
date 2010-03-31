TEMPLATE = app
TARGET = email_archiver
QT += core \
    gui \
    sql \
    network
HEADERS += src/archivermain.h \
    src/messagedetailsmodel.h \
    src/messagemodel.h \
    src/mailmessage.h \
    src/mboximporter.h \
    src/archiver.h
SOURCES += src/archivermain.cpp \
    src/messagedetailsmodel.cpp \
    src/messagemodel.cpp \
    src/mailmessage.cpp \
    src/mboximporter.cpp \
    src/archiver.cpp \
    src/main.cpp
FORMS += src/archivermain.ui \
    src/archiver.ui
RESOURCES += 
