import QtQuick 2.0

Item {
    id: library_element
    property var element_view: null
    property string element_text: ""
//    property var playbutton_elem: playbutton_element
    width: element_view.width
    height: 40

    function onPlayTouched() {

    }

    function onPressAndHold() {

    }

    function onClicked() {

    }

    function onDoubleClicked() {

    }

    Rectangle {
        anchors.margins: 5
        anchors.fill: parent

        border {
            color: "black"
            width: 1
        }

        BottomPanelButton {
            id: playbutton_element
            objectName: "playbutton"
            anchors.left: parent
            anchors.verticalCenter: parent.verticalCenter
            width: 20
            height: 20
            iconSource: "qrc:/resources/images/play.svg"
            function onTouched() {
                library_element.onPlayTouched()
//                console.log("Play touched")
                //mediaplayer.playToggle()
                //console.log(currentTrack.trackServerPath)
                //mediaplayer.currentTrackPath(currentTrack.trackServerPath)
            }
        }



        Text {
            id: text_element
            anchors.verticalCenter: playbutton_element.verticalCenter
            anchors.left: playbutton_element.right
            renderType: Text.NativeRendering
            text: element_text
//            text: element_model.trackTitle
        }

        MouseArea {
            id: mouse_area_element
            height: 40
            width: parent.width - playbutton_element.width
            anchors.left: playbutton_element.right
            onPressAndHold: library_element.onPressAndHold()
            onClicked: library_element.onClicked()
            onDoubleClicked: library_element.onDoubleClicked()
//                console.log("track press and hold")
//                trackView.currentIndex = model.index
//                currentTrack = model
//                stackView.push(Qt.resolvedUrl("TrackInfoPage.qml"))
//            }
//            onClicked: {
//                console.log("track click")
//                currentTrack = model
//            }
//            onDoubleClicked: {
//                console.log("track double click")
//                currentTrack = model
//                mediaplayer.currentTrack = model.trackObject
//                mediaplayer.resetPlaylist()
//            }
        }
    }

}
