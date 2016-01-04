import QtQuick 2.0

Item {
    id: mamabutton
    property alias iconSource: icon.source
    property alias iconRotation: icon.rotation

    function onTouched() {

    }

    function onPressAndHold() {

    }

    Image {
        id: icon
        anchors.fill: parent
        anchors.right: parent.right
        anchors.top: parent.top
        source: ""
        rotation: 0
    }

    MouseArea {
        anchors.fill: parent
        onPressed: {
            icon.opacity = 0.5
        }
        onReleased: {
            icon.opacity = 1
        }
        onClicked: mamabutton.onTouched()
        onPressAndHold: mamabutton.onPressAndHold()
    }
}

