import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: playingButton

    function onTouched() {
    }
    function onPressAndHold() {
    }

    property alias iconSource: icon.source
    property alias iconRotation: icon.rotation
    property color iconColor: settings.globalAccentColor

    MouseArea {
        id: buttonMouseArea

        anchors.fill: parent

        onPressed: icon.opacity = 0.5
        onReleased: icon.opacity = 1

        onClicked: playingButton.onTouched()
        onPressAndHold: playingButton.onPressAndHold()

        Image {
            id: icon
            sourceSize.height: 60
            sourceSize.width: 60
            anchors.fill: parent
            source: ""
            rotation: 0
        }

        ColorOverlay {
            id: iconOverlay
            anchors.fill: icon
            source: icon
            color: iconColor
            rotation: iconRotation
        }
    }
}
