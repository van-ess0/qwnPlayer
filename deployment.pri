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

#macosx {
#    QMAKE_MAC_SDK.macosx.version = 10.11
#    QMAKE_MAC_SDK = macosx10.11
#    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
#    QMAKE_INFO_PLIST = Info.plist
#}

ios {
    QMAKE_INFO_PLIST = resources/ios/Info.plist
    DISTFILES += resources/ios/Info.plist
}

macx {
    QMAKE_INFO_PLIST = resources/ios/Info.plist
    DISTFILES += resources/ios/Info.plist
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

#win32 {
#    install_it.path = $$OUT_PWD
#    install_it.files += $$PWD/settings.conf
#    INSTALLS += install_it
#}

packagesExist(sailfishapp) {
    CONFIG += sailfishapp sailfishapp_i18n
    SAILFISHAPP_ICONS = 86x86
    DISTFILES += rpm/qwnPlayer.yaml \
    rpm/qwnPlayer.changes.in \
    rpm/qwnPlayer.spec \
    qwnPlayer.desktop \
    icons/86x86/qwnPlayer.png
}
export(INSTALLS)

