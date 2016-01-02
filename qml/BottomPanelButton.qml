import QtQuick 2.0

Item {

    id: mamabutton
    property string iconSource: "";

    function onTouched() {

    }

    function onPressAndHold() {

    }

    Image {
        id: icon
        anchors.fill: parent
        anchors.right: parent.right
        anchors.top: parent.top
        source: mamabutton.iconSource
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

