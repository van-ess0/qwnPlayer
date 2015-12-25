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

        delegate: Item {
            width: albumView.width
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
                    text: model.albumName
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        albumView.currentIndex = model.index
                        currentAlbumId = model.albumId
                        currentAlbum = model
                        stackView.push(Qt.resolvedUrl("TrackList.qml"))
                    }
                }
            }

        }
    }
}

