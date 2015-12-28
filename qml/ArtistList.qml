import QtQuick 2.5
import QtQuick.Controls 1.4

Item {

    Text {
        text: qsTr("This is artist Page")
    }

    width: parent.width
    height: parent.height

    ListView {
        id: artistView

        model: artistModel

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }

        highlightFollowsCurrentItem: true

        delegate: LibraryElement {
            element_view: artistView
            element_text: model.artistName

            function setCurrentElement() {
                console.log("artist set current element")
                artistView.currentIndex = model.index
                currentArtistId = model.artistId
                mediaplayer.currentArtist = model
            }

            function onPlayTouched() {
                setCurrentElement()
                console.log("Play artist touched")

                mediaplayer.stopPlaying()
                mediaplayer.settingCurrentArtistToPlaylist()
                mediaplayer.startPlaying()
            }

            function onPressAndHold() {
                setCurrentElement()
                console.log("artist press and hold")
            }

            function onClicked() {
                setCurrentElement()
                console.log("artist click")
            }

            function onDoubleClicked() {
                setCurrentElement()
                console.log("artist double click")
                stackView.push(Qt.resolvedUrl("AlbumList.qml"))
            }
        }
    }
}

