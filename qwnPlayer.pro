TEMPLATE = app

QT += qml quick network multimedia svg
CONFIG += c++11
DEFINES += QT_MESSAGELOGCONTEXT

SOURCES += \
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
    src/QwnSettings.cpp \
    src/main.cpp \
    src/QwnImageProvider.cpp \
    src/NotificationClient.cpp

RESOURCES += \
    media.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
#  QML_IMPORT_PATH =

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
    src/Macros.h \
    src/QwnImageProvider.h \
    src/NotificationClient.h

# SFOS

DISTFILES += \
    rpm/qwnPlayer.yaml \
    rpm/qwnPlayer.changes.in \
    rpm/qwnPlayer.spec \
    qwnPlayer.desktop \
    icons/86x86/qwnPlayer.png

android: {
    QT += androidextras
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    DISTFILES += \
        android/AndroidManifest.xml \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew \
        android/res/values/libs.xml \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew.bat \
        android/src/org/qwnplayer/qwnplayer/NotificationClient.java
}
