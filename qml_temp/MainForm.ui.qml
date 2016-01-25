import QtQuick 2.4

Item {
    id: item1
    width: 480
    height: 800
    antialiasing: false
    z: 0
    rotation: 0
    scale: 1

    Column {
        id: column1
        spacing: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Rectangle {
            id: rectangle1
            height: 80
            color: "#3b3737"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            MouseArea {
                id: mouseArea1
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0

                Image {
                    id: image1
                    width: 80
                    sourceSize.height: 80
                    sourceSize.width: 80
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    source: "hamburgermenu.svg"
                }

                Text {
                    id: text1
                    color: "#87ceeb"
                    text: qsTr("Some text here")
                    style: Text.Normal
                    font.pixelSize: 32
                    font.family: "Tahoma"
                    textFormat: Text.AutoText
                    wrapMode: Text.NoWrap
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    anchors.right: parent.right
                    anchors.rightMargin: 80
                    anchors.left: image1.right
                    anchors.leftMargin: 10
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: parent.top
                    anchors.topMargin: 0
                }
            }
        }

        Rectangle {
            id: rectangle2
            height: 603
            color: "#000000"
            anchors.top: rectangle1.bottom
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Rectangle {
            id: rectangle3
            color: "#282525"
            anchors.top: rectangle2.bottom
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }
    }
}
