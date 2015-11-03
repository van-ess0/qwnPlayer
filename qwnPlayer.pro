TEMPLATE = app

QT += qml quick network widgets multimedia multimediawidgets
CONFIG += c++11

SOURCES += main.cpp \
    OwnCloudClient.cpp \
    Track.cpp \
    Album.cpp \
    Artist.cpp \
    ResponseDecoder.cpp \
    MainWindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    OwnCloudClient.h \
    Track.h \
    Album.h \
    Artist.h \
    ResponseDecoder.h \
    MainWindow.h

FORMS += \
    MainWindow.ui
