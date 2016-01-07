import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    id: playlistPage
    objectName: "PlaylistPage"

    width: parent.width
    height: parent.height

    ListView {
        id: playlistView

        model: currentPlaylist

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
            element_view: playlistView
            element_text: model.trackTitle

            function setCurrentElement() {
                console.log("playlist set current element")
                playlistView.currentIndex = model.index
//                currentArtistId = model.artistId
//                mediaplayer.currentArtist = model
            }

            function onPlayTouched() {
                setCurrentElement()
                console.log("Play artist touched")

//                mediaplayer.stopPlaying()
//                mediaplayer.settingCurrentArtistToPlaylist()
//                mediaplayer.startPlaying()
            }

            function onPressAndHold() {
                setCurrentElement()
                console.log("playlist element press and hold")
            }

            function onClicked() {
                setCurrentElement()
                console.log("playlist element click")
//                stackView.push(Qt.resolvedUrl("AlbumList.qml"))
            }

            function onDoubleClicked() {
                setCurrentElement()
                console.log("playlist element double click")
                mediaplayer.changeCurrentTrackIndex(model.index)
//                stackView.push(Qt.resolvedUrl("AlbumList.qml"))
            }
        }
    }

    function updateCurrentIndex(index) {
        playlistView.currentIndex = index
    }

    Component.onCompleted: {
        updateCurrentIndex(mediaplayer.currentTrackIndex)
    }
}
