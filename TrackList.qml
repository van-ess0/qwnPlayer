import QtQuick 2.0

Item {
    id: trackListView

    Text {
        text: qsTr("This is track Page")
    }

    width: parent.width
    height: parent.height

    ListView {
        id: trackView

        model: artistModel.subModelFromId(currentArtistId).subModelFromId(currentAlbumId)
//        model: currentAlbum

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }
        highlightFollowsCurrentItem: true

        delegate: LibraryElement {
            element_view: trackView
            element_text: model.trackTitle

            function setCurrentElement() {
                console.log("track set current element")
                trackView.currentIndex = model.index
                currentTrack = model

            }

            function onPlayTouched() {
                setCurrentElement()
                console.log("Play track touched")
            }

            function onPressAndHold() {
                setCurrentElement()
                console.log("track press and hold")
            }

            function onClicked() {
                setCurrentElement()
                console.log("track click")
            }

            function onDoubleClicked() {
                setCurrentElement()
                console.log("track double click")
                stackView.push(Qt.resolvedUrl("TrackInfoPage.qml"))
            }
        }
    }
}

