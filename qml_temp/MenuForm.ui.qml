import QtQuick 2.4

Item {
    id: item1
    width: 480
    height: 800

    Column {
        id: column1
        anchors.right: parent.right
        anchors.rightMargin: 80
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        Row {
            id: homeRow
            width: 400
            height: 80
            anchors.top: parent.top
            anchors.topMargin: 80

            MouseArea {
                id: mouseArea1
                anchors.bottomMargin: 0
                Image {
                    id: image1
                    width: 80
                    source: "home.svg"
                    sourceSize.width: 80
                    anchors.bottomMargin: 0
                    anchors.topMargin: 0
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    anchors.leftMargin: 0
                    sourceSize.height: 80
                }

                Text {
                    id: text1
                    color: "#87ceeb"
                    text: qsTr("Home")
                    anchors.left: image1.right
                    verticalAlignment: Text.AlignVCenter
                    anchors.topMargin: 0
                    anchors.rightMargin: 0
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 32
                    anchors.bottomMargin: 0
                    font.bold: true
                    anchors.right: parent.right
                    textFormat: Text.AutoText
                    font.family: "Tahoma"
                    wrapMode: Text.NoWrap
                    anchors.leftMargin: 10
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom
                    style: Text.Normal
                }
                anchors.rightMargin: 0
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 0
            }
        }
    }
}
