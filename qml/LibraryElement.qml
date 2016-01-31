import QtQuick 2.0

Item {
    id: library_element
    property var element_view: null
    property string element_text: ""
    property bool elemet_playbutton_visible: true

    width: element_view.width
    height: 60 * scaleFactor

    property color accentColor: settings.globalAccentColor
    property color rectangleColor: settings.globalRectangleColor
    property color borderColor: settings.globalRectangleBorderColor

    function onPlayTouched() {

    }

    function onPressAndHold() {

    }

    function onClicked() {

    }

    function onDoubleClicked() {

    }

    Rectangle {
        anchors.margins: 1
        anchors.fill: parent

        color: rectangleColor

        border {
            color: borderColor
            width: 2 * scaleFactor
        }

        PlayingPanelButton {
            id: playbutton_element
            objectName: "playbutton"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: parent.height
            width: height
            iconSource: "qrc:/resources/images/play.svg"
            iconColor: accentColor
            function onTouched() {
                library_element.onPlayTouched()
            }

            visible: library_element.elemet_playbutton_visible
        }

        Text {
            color: accentColor
            font.pixelSize: 18 * scaleFactor
            id: text_element
            anchors.verticalCenter: playbutton_element.verticalCenter
            anchors.left: playbutton_element.right
            renderType: Text.NativeRendering
            text: element_text
        }

        MouseArea {
            id: mouse_area_element
            height: parent.height
            width: parent.width - playbutton_element.width
            anchors.left: playbutton_element.right
            onPressAndHold: library_element.onPressAndHold()
            onClicked: library_element.onClicked()
            onDoubleClicked: library_element.onDoubleClicked()
        }
    }

}

