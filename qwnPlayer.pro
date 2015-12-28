TEMPLATE = app

QT += qml quick network widgets multimedia multimediawidgets svg
CONFIG += c++11
DEFINES += QT_MESSAGELOGCONTEXT

SOURCES += src/main.cpp \
    src/OwnCloudClient.cpp \
    src/Track.cpp \
    src/Album.cpp \
    src/Artist.cpp \
    src/ResponseDecoder.cpp \
    src/QwnMediaPlayer.cpp \
    src/MusicLibrary.cpp \
    Models/ListModel.cpp \
    Models/SubListedListModel.cpp \
    src/GlobalIndex.cpp \
    src/SettingsManager.cpp \
    src/QwnSettings.cpp

RESOURCES += qml.qrc \
    media.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/OwnCloudClient.h \
    src/Track.h \
    src/Album.h \
    src/Artist.h \
    src/ResponseDecoder.h \
    src/QwnMediaPlayer.h \
    src/MusicLibrary.h \
    Models/ListItem.h \
    Models/ListModel.h \
    Models/SubListedListItem.h \
    Models/SubListedListModel.h \
    src/SingletonTemplate.h \
    src/GlobalIndex.h \
    src/SettingsManager.h \
    src/QwnSettings.h \
    src/Macros.h

DISTFILES += \
    settings.conf \
    resources/ios/Info.plist

