import QtQuick 2.5

Item {

    id: mamabutton
    property string iconSource: "";

    function onTouched() {

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
    }
}

