import QtQuick 2.0

Item {
    id: row
    height: 80 * scaleFactor
    anchors.top: parent.top
    anchors.topMargin: 0
    anchors.right: parent.right
    anchors.rightMargin: 0
    anchors.left: parent.left
    anchors.leftMargin: 0


    property alias iconSource: icon.source
    property alias label: text.text

    function onButtonClicked()
    {
        console.log("on button clicked")
    }

    Rectangle {
        id: rectangle
        color: "#000000"
        radius: 0
        border.width: 1
        anchors.bottomMargin: 0
        border.color: "#171717"
        MouseArea {
            id: mouseArea
            x: 0
            y: 0
            anchors.bottomMargin: 0
            onClicked: row.onButtonClicked()
            Image {
                id: icon
                width: 76 * scaleFactor
                source: "hamburgermenu.svg"
                sourceSize.width: 80 * scaleFactor
                anchors.bottomMargin: 2
                anchors.topMargin: 2
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.leftMargin: 2
                sourceSize.height: 80 * scaleFactor
            }

            Text {
                id: text
                color: "#87ceeb"
                text: qsTr("qwnPlayer")
                anchors.left: icon.right
                verticalAlignment: Text.AlignVCenter
                anchors.topMargin: 0
                anchors.rightMargin: 0
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 32 * scaleFactor
                anchors.bottomMargin: 0
                font.bold: true
                anchors.right: parent.right
                textFormat: Text.AutoText
                font.family: "Tahoma"
                wrapMode: Text.NoWrap
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                style: Text.Normal
                font.capitalization: Font.AllUppercase
            }
            anchors.rightMargin: 0
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.leftMargin: 0
        }
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 0
    }
}


//Item {
//    id: mamabutton

//    property int minWidth: 40
//    property int maxWidth: 200

//    property alias iconSource: icon.source
//    property alias label: text.text
//    property alias textVisibility: text.visible

//    width: minWidth
//    height: minWidth
//    function onTouched() {

//    }

//        Text {
//            id: text
//            width: mamabutton.width - mamabutton.minWidth
//            anchors.left: icon.right
//            anchors.right: parent.right
//            text: ""
//            visible: false
//            Behavior on visible {
//                NumberAnimation {
//                    duration: 400
//                    easing.type: Easing.InQuad
//                }
//            }

//        }

//        Image {
//            id: icon
//            width: parent.height
//            height: width
//            anchors.left: parent.left
//            anchors.top: parent.top
//            source: mamabutton.iconSource
//        }

//        MouseArea {
//            anchors.fill: parent
//            onPressed: {
//                icon.opacity = 0.5
//                text.opacity = 0.5
//            }
//            onReleased: {
//                icon.opacity = 1
//                text.opacity = 1
//            }
//            onClicked: mamabutton.onTouched()
//        }
//}

