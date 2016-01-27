import QtQuick 2.0


ListView {
    id: libraryView
    objectName: "LibraryView"

    model: null

    anchors.margins: 5 * scaleFactor
    anchors.fill: parent
//    z: stackView.z
    spacing: 5 * scaleFactor
    clip: true

    property color accentColor: settings.globalAccentColor

    highlight: Rectangle {
        color: accentColor
    }

    highlightFollowsCurrentItem: true

    function updateCurrentIndex(index) {
        libraryView.currentIndex = index
    }

    delegate: LibraryElement {

        Component.onCompleted: {
            if ("SettingsView" === libraryView.objectName
                    || "PlaylistView" === libraryView.objectName) {
                elemet_playbutton_visible = false
            }
        }

        id: libraryElement
        element_view: libraryView
        element_text: {
            if ("ArtistView" === libraryView.objectName) {
                model.artistName
            } else if ("AlbumView" === libraryView.objectName) {
                model.albumYear + " - " + model.albumName
            } else if ("TrackView" === libraryView.objectName) {
                model.trackTitle
            } else if ("SettingsView" === libraryView.objectName) {
                model.text
            } else if ("PlaylistView" === libraryView.objectName) {
                model.trackTitle
            }
        }
        function setCurrentElement() {
            console.log("artist set current element")
            libraryView.currentIndex = model.index

            if ("ArtistView" === libraryView.objectName) {
                currentArtistId = model.artistId
                mediaplayer.currentArtist = model
            } else if ("AlbumView" === libraryView.objectName) {
                currentAlbumId = model.albumId
                mediaplayer.currentAlbum = model
            } else if ("TrackView" === libraryView.objectName) {
                mediaplayer.currentTrack = model
            }


        }

        function onPlayTouched() {
            setCurrentElement()


            mediaplayer.stopPlaying()

            if ("ArtistView" === libraryView.objectName) {
                console.log("Play artist touched")
                mediaplayer.settingCurrentArtistToPlaylist()
            } else if ("AlbumView" === libraryView.objectName) {
                console.log("Play album touched")
                mediaplayer.settingCurrentAlbumToPlaylist()
            } else if ("TrackView" === libraryView.objectName) {
                console.log("Play track touched")
                mediaplayer.settingCurrentTrackToPlaylist()
            }



            mediaplayer.startPlaying()
        }

        function onPressAndHold() {
            setCurrentElement()
            console.log("artist press and hold")
        }

        function onClicked() {
            setCurrentElement()

            if ("ArtistView" === libraryView.objectName) {
                console.log("artist click")
                mainForm.pushToStack("AlbumList.qml")
            } else if ("AlbumView" === libraryView.objectName) {
                console.log("album click")
                mainForm.pushToStack("TrackList.qml")
            } else if ("TrackView" === libraryView.objectName) {
                console.log("track click")
                mainForm.pushToStack("TrackInfoPage.qml")
            } else if ("SettingsView" === libraryView.objectName) {
                console.log("settings click")
                mainForm.pushToStack(model.pageUrl)
                if (mainForm.stackCurrentItem().objectName === "ConnectionPage") {
                    console.log("init settings")
                    if (settings.is_initialized === true) {
                        mainForm.stackCurrentItem().onInitFields()
                    } else {
                        settings.initialize()
                    }

                }
            }

        }

        function onDoubleClicked() {
            setCurrentElement()
            if ("PlaylistView" === libraryView.objectName) {
                console.log("playlist element double click")
                mediaplayer.changeCurrentTrackIndex(model.index)
            }
        }
    }
}

