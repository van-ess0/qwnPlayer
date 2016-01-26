import QtQuick 2.0

Item {
    id: playingButton

    function onTouched() {
    }
    function onPressAndHold() {
    }

    property alias iconSource: icon.source
    property alias iconRotation: icon.rotation

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
    }
}
