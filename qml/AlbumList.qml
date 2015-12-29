import QtQuick 2.5
import QtQuick.Controls 1.4

Item {

    id: albumListView

    Text {
        text: qsTr("This is album Page")
    }

    width: parent.width
    height: parent.height

    ListView {
        id: albumView

        model: artistModel.subModelFromId(currentArtistId)

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }
        highlightFollowsCurrentItem: true

        delegate: LibraryElement {
            element_view: albumView
            element_text: model.albumYear + " - " + model.albumName

            function setCurrentElement() {
                console.log("album set current element")
                albumView.currentIndex = model.index
                currentAlbumId = model.albumId
                mediaplayer.currentAlbum = model
                playingTrack.album = model.albumName
            }

            function onPlayTouched() {
                setCurrentElement()
                console.log("Play album touched")

                mediaplayer.stopPlaying()
                mediaplayer.settingCurrentAlbumToPlaylist()
                mediaplayer.startPlaying()
            }

            function onPressAndHold() {
                setCurrentElement()
                console.log("album press and hold")
            }

            function onClicked() {
                setCurrentElement()
                console.log("album click")
            }

            function onDoubleClicked() {
                setCurrentElement()
                console.log("album double click")
                stackView.push(Qt.resolvedUrl("TrackList.qml"))
            }
        }
    }
}

