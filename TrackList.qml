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

        delegate: Item {
            width: trackView.width
            height: 40

            Rectangle {
                anchors.margins: 5
                anchors.fill: parent
                radius: height / 2

                border {
                    color: "black"
                    width: 1
                }
                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: model.trackTitle
                }

                MouseArea {
                    anchors.fill: parent
                    onPressAndHold: {
                        console.log("track press and hold")
                        trackView.currentIndex = model.index
                        currentTrack = model
                        stackView.push(Qt.resolvedUrl("TrackInfoPage.qml"))
                    }
                    onClicked: {
                        console.log("track click")
                        currentTrack = model
                    }
                    onDoubleClicked: {
                        console.log("track double click")
                        currentTrack = model
                        mediaplayer.currentTrack = model
                        mediaplayer.resetPlaylist()
                    }
                }
            }

        }
    }
}

