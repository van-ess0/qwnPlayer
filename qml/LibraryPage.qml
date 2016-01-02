import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

//    Text {
//        text: qsTr("This is library Page")
//    }

    width: parent.width
    height: parent.height

    ArtistList {

    }

    /*

    ListModel {
        id: listmodel

        ListElement {
            color: "orange"
            name: "first"
        }
        ListElement {
            color: "lightgreen"
            name: "second"
        }
        ListElement {
            color: "orchid"
            name: "third"
        }
        ListElement {
            color: "tomato"
            name: "fourth"
        }
    }

    ListView {
        id: view

        model: roomModel

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }
        highlightFollowsCurrentItem: true

        delegate: Item {
            width: view.width
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
                    text: model.artistName
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: view.currentIndex = model.index
                }
            }

        }
    }*/
}
