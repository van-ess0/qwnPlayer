import QtQuick 2.0

Item {

    id: mamabutton
    property string iconSource: "";
    //property color colorel: "green";
    property int minWidth: 40
    property int maxWidth: 200
    property string label: ""
    property bool textopacity: false
    width: minWidth
    height: minWidth
    function onTouched() {

    }

        Text {
            id: text
            width: mamabutton.width - mamabutton.minWidth
            anchors.left: icon.right
            anchors.right: parent.right
            text: mamabutton.label
            visible: mamabutton.textopacity
            Behavior on visible {
                NumberAnimation {
                    duration: 400
                    easing.type: Easing.InQuad
                }
            }

        }

        Image {
            id: icon
            width: parent.height
            height: width
            anchors.left: parent.left
            anchors.top: parent.top
            source: mamabutton.iconSource
        }

        MouseArea {
            anchors.fill: parent
            onPressed: {
                icon.opacity = 0.5
                text.opacity = 0.5
            }
            onReleased: {
                icon.opacity = 1
                text.opacity = 1
            }
            onClicked: mamabutton.onTouched()
        }
}

