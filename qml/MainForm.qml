import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    id: mainForm
    width: window.width
    height: window.height
    antialiasing: false
    z: 0
    rotation: 0
    scale: 1

    property var stackTop: topRectangleMain.bottom
    property var stackBottom: bottomPanel.top
    property var stackLeft: mainForm.left
    property var stackRight: mainForm.right

    property alias titleLabel: titleText.text

    function onMenuButtonClicked() {
        console.log("on menu button clicked")
    }

    Rectangle {
        id: topRectangleMain
        border.color: "#171717"
        height: 80 * scaleFactor
        color: "#000000"
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        MouseArea {
            id: titleMouseArea
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Image {
                id: titleImage
                width: 76 * scaleFactor
                height: 76 * scaleFactor
                sourceSize.height: 80 * scaleFactor
                sourceSize.width: 80 * scaleFactor
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 2
                source: "qrc:/resources/images/blue/hamburgermenu_blue.svg"
            }

            Text {
                id: titleText
                color: "#87ceeb"
                text: qsTr("Some text here")
                style: Text.Normal
                font.pixelSize: 32 * scaleFactor
                font.family: "Tahoma"
                font.capitalization: Font.AllUppercase
                textFormat: Text.AutoText
                wrapMode: Text.NoWrap
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.right: parent.right
                anchors.rightMargin: 80
                anchors.left: titleImage.right
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
            }

            onClicked: mainForm.onMenuButtonClicked()
        }
    }


    Rectangle {
        id: midRectangleMain
//        x: 0
//        y: 80 * scaleFactor
        height: 600 * scaleFactor
        color: "#000000"
        anchors.top: topRectangleMain.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120 * scaleFactor
    }

    PlayingPanel {
        id: bottomPanel
        border.color: "#171717"
//        x: 0
//        y: 683 * scaleFactor
        height: 120 * scaleFactor
        color: "#000000"
        anchors.top: midRectangleMain.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    function onProgressChanged(progress) {
        bottomPanel.onProgressChanged(progress)
    }

    function onDurationChanged(duration) {
        bottomPanel.onDurationChanged(duration)
    }

    function onPlayingStateChanged(state) {
        bottomPanel.onPlayingStateChanged(state)
    }
}
