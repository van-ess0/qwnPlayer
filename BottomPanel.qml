import QtQuick 2.5
import com.qwnplayer 1.0

Item {

    height: 100
    width: parent.width
    anchors.bottom: parent.bottom

    QwnMediaPlayer {
        id: mediaplayer
//        onKeyGenerated: {
//            if (success) {
//                console.log("Key generation succeeded.")
//            } else {
//                console.log("Key generation failed.")
//            }
//        }
//        onTestSig: {
//            console.log("From C++")
//        }
    }
    Rectangle {
        anchors.fill: parent
        color: "green"


        BottomPanelButton {
            id: playbutton
            objectName: "playbutton"
            anchors.centerIn: parent
            width: 40
            height: 40
            iconSource: "qrc:/resources/images/play.svg"
//            signal qmlSignal(string msg)
//            signal qmlSignalEmpty()
            function onTouched() {
                console.log("Play touched")
//                playbutton.qmlSignal("Hi from qml")
//                playbutton.qmlSignalEmpty()
//                mediaplayer.qmlSlotEmpty()
                mediaplayer.playToggle()
            }
        }

        BottomPanelButton {
            id: prevbutton
            anchors.verticalCenter: playbutton.verticalCenter
            anchors.right: playbutton.left
            width: 20
            height: 20
            iconSource: "qrc:/resources/images/previous.svg"

            function onTouched() {
                console.log("Prev touched")
                mediaplayer.prevTrack()
            }
        }

        BottomPanelButton {
            id: nextbutton
            anchors.verticalCenter: playbutton.verticalCenter
            anchors.left: playbutton.right
            width: 20
            height: 20
            iconSource: "qrc:/resources/images/next.svg"

            function onTouched() {
                console.log("Next touched")
                mediaplayer.nextTrack()
            }
        }

        BottomPanelButton {
            id: shufflebutton
            anchors.verticalCenter: playbutton.verticalCenter
            x: prevbutton.x - 40
            width: 20
            height: 20
            iconSource: "qrc:/resources/images/shuffle.svg"

            function onTouched() {
                console.log("Shuffle touched")
                mediaplayer.shuffleToggle()
            }
        }

        BottomPanelButton {
            id: cyclebutton
            anchors.verticalCenter: playbutton.verticalCenter
            x: nextbutton.x + 40
            width: 20
            height: 20
            iconSource: "qrc:/resources/images/cycle.svg"

            function onTouched() {
                console.log("Cycle touched")
                mediaplayer.cycleToggle()
            }
        }

    }
}

