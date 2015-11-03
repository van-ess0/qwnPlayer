import QtQuick 2.0

Rectangle{

    id: mamabutton
    property string iconSource: "";
    property color color: "green";
    property int minWidth: 0
    property int maxWidth: 0
    property string label: ""
    height: minWidth
    function onTouched() {

    }
    Rectangle {

        //id: smallbutton
        width: parent.width
        height: parent.heigth
        anchors.top: parent.top
        anchors.left: parent.left
        color: parent.color

        Behavior on width {
            NumberAnimation {
                duration: 400
                easing.type: Easing.OutQuad
            }
        }

        Image {
            id: icon
            width: mamabutton.minWidth
            height: width
            anchors.right: parent.right
            source: mamabutton.iconSource
        }

        Text {
            width: parent.width - mamabutton.minWidth
            anchors.left: parent.left
            anchors.right: parent.right
            text: mamabutton.label
        }

        MouseArea {
            anchors.fill: parent
            onPressed: icon.opacity = 0.5
            onReleased: icon.opacity = 1
            onClicked: mamabutton.onTouched()
        }
    }

}

