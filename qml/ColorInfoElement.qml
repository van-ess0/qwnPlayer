import QtQuick 2.0
import QtQuick.Controls 1.2

Row {

    property alias textLabel: colorLabel.text
    property int colorPropertyNumber: 0

    id: colorRow
    spacing: parent.spacing
    height: 85 * scaleFactor

    Rectangle {
        color: themeSettingsPage.getColor(colorPropertyNumber) // for Accent color
        height: parent.height
        width: height
        border.width: 3
        border.color: colorPropertyNumber == 1 ? "white" : themeSettingsPage.systemAccentColor
        MouseArea {
            anchors.fill: parent
            onClicked: {
                themeSettingsPage.setCurrentColor(colorPropertyNumber)
                colorDialog.open()
            }
        }
    }

    Label {
        color: themeSettingsPage.systemAccentColor
        font.pixelSize: 18 * scaleFactor
        font.family: "Tahoma"
        text: themeSettingsPage.getColor(colorPropertyNumber)
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        id: colorLabel
        font.pixelSize: 18 * scaleFactor
        font.family: "Tahoma"
        color: themeSettingsPage.systemAccentColor
        text: "color:"
        anchors.verticalCenter: parent.verticalCenter
    }
}
