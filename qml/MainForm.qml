import QtQuick 2.0
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

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

    property var standartSquareSize: 60

    property color accentColor: settings.globalAccentColor
    property color backgroundColor: settings.globalBackgroundColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    Rectangle {
        id: topRectangleMain
        border.color: rectangleBorderColor
        height: standartSquareSize * scaleFactor
        color: backgroundColor
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
                width: (standartSquareSize - 4) * scaleFactor
                height: (standartSquareSize - 4) * scaleFactor
                sourceSize.height: standartSquareSize * scaleFactor
                sourceSize.width: standartSquareSize * scaleFactor
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.top: parent.top
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.leftMargin: 2
                source: "qrc:/resources/images/hamburgermenu.svg"
            }

            ColorOverlay {
                id: titleImageOverlay
                anchors.fill: titleImage
                source: titleImage
                color: accentColor
            }

            Text {
                id: titleText
                color: accentColor
                text: qsTr("Some text here")
                style: Text.Normal
                font.pixelSize: 24 * scaleFactor
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
        height: 600 * scaleFactor
        color: backgroundColor
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
        border.color: rectangleBorderColor
        height: 120 * scaleFactor
        color: backgroundColor
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
