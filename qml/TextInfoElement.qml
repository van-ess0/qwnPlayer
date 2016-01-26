import QtQuick 2.0

Rectangle {
    property alias textLabel: text.text

    property color accentColor: settings.globalAccentColor
    property color rectangleColor: settings.globalRectangleColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    width: parent.width
    height: 60 * scaleFactor
    color: rectangleColor
    border.width: 1
    border.color: rectangleBorderColor

    Text {
        id: text
        color: accentColor
        font.family: "Tahoma"
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        horizontalAlignment: Text.AlignLeft
        text: "Empty"
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.fill: parent
        font.pixelSize: 16 * scaleFactor
        verticalAlignment: Text.AlignVCenter
    }
}
