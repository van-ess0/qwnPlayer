import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: row
    property var standartSquareSize: 60
    height: standartSquareSize * scaleFactor
    anchors.top: parent.top
    anchors.topMargin: 0
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0


    property alias iconSource: icon.source
    property alias label: text.text
    property bool isFontUppercase: false
    property alias textVisibility: text.visible

    property color iconColor: settings.globalAccentColor
    property color labelColor: settings.globalAccentColor
    property color backgroundColor: settings.globalBackgroundColor
    property color borderColor: settings.globalRectangleBorderColor

    function onButtonClicked()
    {
        console.log("on button clicked")
    }

    Rectangle {
        id: rectangle
        radius: 0
        color: backgroundColor
        border.width: 1
        border.color: borderColor
        anchors.bottomMargin: 0
        MouseArea {
            id: mouseArea
            x: 0
            y: 0
            anchors.bottomMargin: 0
            onClicked: row.onButtonClicked()
            Image {
                id: icon
                width: (standartSquareSize- 4) * scaleFactor
                height: (standartSquareSize - 4) * scaleFactor
                source: ""
                sourceSize.width: standartSquareSize * scaleFactor
                sourceSize.height: standartSquareSize * scaleFactor
                anchors.bottomMargin: 2
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 2
            }

            ColorOverlay {
                id: iconOverlay
                anchors.fill: icon
                source: icon
                color: iconColor
            }

            Text {
                id: text
                text: qsTr("qwnPlayer")
                color: labelColor
                anchors.left: icon.right
                verticalAlignment: Text.AlignVCenter
                anchors.topMargin: 0
                anchors.rightMargin: 0
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 26 * scaleFactor
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
                font.capitalization: isFontUppercase ? Font.AllUppercase : Font.MixedCase
                visible: false
            }

            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
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

