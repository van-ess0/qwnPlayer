import QtQuick 2.0


ListView {
    id: libraryView
    objectName: "LibraryView"

    model: null

    anchors.margins: 10
    anchors.fill: parent
    z: stackView.z
    spacing: 10
    clip: true

    highlight: Rectangle {
        color: "skyblue"
    }

    highlightFollowsCurrentItem: true

    delegate: LibraryElement {
        //            function setElementText() {

        //            }

        id: libraryElement
        element_view: libraryView
        element_text: {
            if ("ArtistView" === libraryView.objectName) {
                model.artistName
            } else if ("AlbumView" === libraryView.objectName) {
                model.albumYear + " - " + model.albumName
            } else if ("TrackView" === libraryView.objectName) {
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
                stackView.push(Qt.resolvedUrl("AlbumList.qml"))
            } else if ("AlbumView" === libraryView.objectName) {
                console.log("album click")
                stackView.push(Qt.resolvedUrl("TrackList.qml"))
            } else if ("TrackView" === libraryView.objectName) {
                console.log("track click")
                stackView.push(Qt.resolvedUrl("TrackInfoPage.qml"))
            }


        }

        function onDoubleClicked() {
            setCurrentElement()
            //                console.log("artist double click")
            //                stackView.push(Qt.resolvedUrl("AlbumList.qml"))
        }
    }
}

