QT       += core gui charts network xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


unix: LIBS += -L$$(HOME)/openssl-1.1.1d -lssl -lcrypto

# If not working on windows, check the path of your openSSL install
win64: LIBS += -LC:/Program Files/OpenSSL-Win64/lib -lssl -lcrypto

INCLUDEPATH += \
    $$PWD/../weatherize


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp \
    calculations.cpp \
    charttool.cpp \
    counter.cpp \
    data.cpp \
    database.cpp \
    locationdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    piechart.cpp \
    xmltosql.cpp

HEADERS += \
    api.hh \
    calculations.hh \
    charttool.h \
    counter.h \
    data.hh \
    database.hh \
    locationdialog.hh \
    mainwindow.h \
    piechart.hh \
    xmltosql.hh

FORMS += \
    locationdialog.ui \
    mainwindow.ui



# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


