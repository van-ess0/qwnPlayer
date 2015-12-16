unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

macx {
  QMAKE_MAC_SDK = macosx10.11
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
}

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

install_it.path = $$OUT_PWD
install_it.files += $$PWD/settings.conf

INSTALLS += install_it

export(INSTALLS)

