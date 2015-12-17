import QtQuick 2.5
import QtQuick.Controls 1.4

Item {

    Text {
        text: qsTr("This is artist Page")
    }

    width: parent.width
    height: parent.height

//    AlbumList {
//        id: albumListView
//    }

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

        delegate: Item {
            width: artistView.width
            height: 40

            Rectangle {
                anchors.margins: 5
                anchors.fill: parent
                radius: height / 2


//                color: model.color

                border {
                    color: "black"
                    width: 1
                }
                Text {
                    anchors.centerIn: parent
                    renderType: Text.NativeRendering
                    text: model
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        artistView.currentIndex = model.index
                        currentArtistId = model.artistId
                        currentArtist = model
                        stackView.push(Qt.resolvedUrl("AlbumList.qml"))
                    }
                }
            }

        }
    }
}

