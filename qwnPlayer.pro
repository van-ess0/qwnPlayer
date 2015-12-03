TEMPLATE = app

QT += qml quick network widgets multimedia multimediawidgets
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
    Models/SubListedListModel.cpp

RESOURCES += qml.qrc \
    media.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

winrt {
    WINRT_MANIFEST.publisher = "Cutehacks!"
#    winphone:equals(WINSDK_VER, 8.0) {
#        WINRT_MANIFEST.capabilities += ID_CAP_NETWORKING ID_CAP_MEDIALIB_AUDIO
#    } else {
#        WINRT_MANIFEST.capabilities += internetClient
#        WINRT_MANIFEST.rotation_preference = "portrait"
#    }
    WINRT_MANIFEST.capabilities += internetClient musicLibrary
    WINRT_MANIFEST.rotation_preference = "portrait"
    CONFIG += windeployqt
}

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
    SingletonTemplate.h

FORMS += \
    MainWindow.ui
