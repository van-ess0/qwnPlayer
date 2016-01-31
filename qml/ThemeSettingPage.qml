import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.1

Item {
    id: themeSettingsPage

    SystemPalette {
        id: palette
    }

    clip: true

    property color systemAccentColor: settings.globalAccentColor
    property color systemBackgroundColor: settings.globalBackgroundColor
    property color systemRectangleColor: settings.globalRectangleColor
    property color systemRectangleBorderColor: settings.globalRectangleBorderColor

    // 0 - no
    // 1 - accent
    // 2 - background
    // 3 - rectangle
    // 4 - rectangle border

    property int currentColorToSet: 0

    function getColor(colorNumber) {
        switch (colorNumber) {
        case 1: return systemAccentColor;
        case 2: return systemBackgroundColor;
        case 3: return systemRectangleColor;
        case 4: return systemRectangleBorderColor;
        default: return "#000000";
        }
    }

    function setColor(value) {
        switch (currentColorToSet) {
        case 1:
            console.log("here")
            settings.globalAccentColor = value
            break
        case 2:
            settings.globalBackgroundColor = value
            break
        case 3:
            settings.globalRectangleColor = value
            break
        case 4:
            settings.globalRectangleBorderColor = value
            break
        default:
            console.log("some error on set color " + value)
            break
        }
    }

    function setCurrentColor(value) {
        currentColorToSet = value
    }

    ColorDialog {
        id: colorDialog
        visible: false
        modality: Qt.WindowModal
        title: "Choose a color"
        showAlphaChannel: true
        onAccepted: {
            console.log("Accepted: " + color)
            themeSettingsPage.setColor(color)
            themeSettingsPage.currentColorToSet = 0
        }
        onRejected: {
            console.log("Rejected")
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 8

        CheckBox {
            style: CheckBoxStyle {
                label: Text {
                    color: systemAccentColor
                    text: "Show menu permanent"
                    font.pixelSize: 18 * scaleFactor
                    font.family: "Tahoma"
                }
            }

            Component.onCompleted: {
                checked = settings.menuShowPermanent
            }

            onCheckedChanged: {
                settings.menuShowPermanent = checked
            }
        }

        ColorInfoElement {
            colorPropertyNumber: 1
            textLabel: "Accent color"
        }

        ColorInfoElement {
            colorPropertyNumber: 2
            textLabel: "Background color"
        }

        ColorInfoElement {
            colorPropertyNumber: 3
            textLabel: "Rectangle color"
        }

        ColorInfoElement {
            colorPropertyNumber: 4
            textLabel: "Borders color"
        }
    }
}
