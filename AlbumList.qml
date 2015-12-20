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
//        model: currentArtist

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
            element_text: model.albumName

            function setCurrentElement() {
                console.log("album set current element")
                albumView.currentIndex = model.index
                currentAlbumId = model.albumId
                currentAlbum = model
            }

            function onPlayTouched() {
                setCurrentElement()
                console.log("Play album touched")
            }

            function onPressAndHold() {
                setCurrentElement()
                console.log("album press and hold")
            }

            function onClicked() {
                setCurrentElement()
                console.log("album click")
                stackView.push(Qt.resolvedUrl("TrackList.qml"))
            }

            function onDoubleClicked() {
                setCurrentElement()
                console.log("album double click")
            }
        }
    }
}

