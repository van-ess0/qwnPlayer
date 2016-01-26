import QtQuick 2.0

Rectangle {
    property alias textLabel: text.text

    width: 400 * scaleFactor
    height: 60 * scaleFactor
    color: "#111111"
    border.width: 1
    border.color: "#171717"

    Text {
        id: text
        color: "skyblue"
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
