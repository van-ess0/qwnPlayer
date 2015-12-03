TEMPLATE = app

QT += qml quick network widgets multimedia multimediawidgets svg
CONFIG += c++11

SOURCES += main.cpp \
    OwnCloudClient.cpp \
    Track.cpp \
    Album.cpp \
    Artist.cpp \
    ResponseDecoder.cpp \
    QwnMediaPlayer.cpp \
    MusicLibrary.cpp \
    Models/ListModel.cpp \
    Models/SubListedListModel.cpp \
    GlobalIndex.cpp

RESOURCES += qml.qrc \
    media.qrc

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
    QwnMediaPlayer.h \
    MusicLibrary.h \
    Models/ListItem.h \
    Models/ListModel.h \
    Models/SubListedListItem.h \
    Models/SubListedListModel.h \
    SingletonTemplate.h \
    GlobalIndex.h

