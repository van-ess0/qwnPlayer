import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    id: bottomPanelItem
    height: parent.height / 7
    width: parent.width
    anchors.bottom: parent.bottom

    function onProgressChanged(progress) {
        console.log("Progress: " + progress)
        progressSlider.value = progress / 1000
    }

    function onDurationChanged(duration) {
        console.log("duration: " + duration)
        progressSlider.maximumValue = Math.round(duration / 1000)
    }


    Rectangle {
        anchors.fill: parent
        color: "grey"

        Text {
            id: currentPos
            text: filling()
            anchors {
                verticalCenter: progressSlider.verticalCenter
                right: progressSlider.left
            }
            function filling()
            {
                var seconds = ""
                var nseconds = (progressSlider.value % 60)
                if (nseconds < 10){

                    seconds = "0" + nseconds.toString()
                }
                else {
                    seconds = nseconds.toString()
                }

                var minutes = ((progressSlider.value - seconds) / 60).toString();

                return (qsTr(minutes + ":" + seconds))
            }
        }

        Text {
            id: trackLength
            text: filling()
            anchors {
                verticalCenter: progressSlider.verticalCenter
                left: progressSlider.right
            }
            function filling()
            {
                var seconds = ""
                var nseconds = progressSlider.maximumValue % 60
                if (nseconds < 10){

                    seconds = "0" + nseconds.toString()
                }
                else {
                    seconds = nseconds.toString()
                }

                var minutes = ((progressSlider.maximumValue - seconds) / 60).toString();

                return (qsTr(minutes + ":" + seconds))
            }
        }

        Slider {
            id: progressSlider
            width: parent.width / 1.5
            maximumValue: 0
            minimumValue: 0
            stepSize: 1.0
            anchors.horizontalCenter: parent.horizontalCenter

            onPressedChanged: {
                if (!pressed) {
                    mediaplayer.setCurrentPosition(value * 1000)
                    console.log("Position set to ", value)
                }
            }

        }

        BottomPanelButton {
            id: playbutton
            objectName: "playbutton"
            anchors.centerIn: parent
            width: bottomPanelItem.height / 2
            height: width
            iconSource: "qrc:/resources/images/play.svg"
            function onTouched() {
                console.log("Play touched")
                mediaplayer.playToggle()
            }
        }

        BottomPanelButton {
            id: prevbutton
            anchors.verticalCenter: playbutton.verticalCenter
            anchors.right: playbutton.left
            width: playbutton.width / 2
            height: width
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
            width: playbutton.width / 2
            height: width
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
            width: playbutton.width / 2
            height: width
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
            width: playbutton.width / 2
            height: width
            iconSource: "qrc:/resources/images/cycle.svg"

            function onTouched() {
                console.log("Cycle touched")
                mediaplayer.cycleToggle()
            }
        }

    }
}

