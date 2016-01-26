import QtQuick 2.0
import QtQuick.Controls 1.1

Rectangle {

    color: "#00000000"

    property var resourcePath: "qrc:/resources/images/blue/"

    function onProgressChanged(progress) {
        console.log("Progress: " + progress)
        progressSlider.value = progress / 1000
    }

    function onDurationChanged(duration) {
        console.log("duration: " + duration)
        progressSlider.maximumValue = Math.round(duration / 1000)
    }

    function onPlayingStateChanged(state) {
        if (state === 1) {
            playButton.iconSource = resourcePath + "pause.svg"
        }
        else {
            playButton.iconSource = resourcePath + "play.svg"
        }
    }

    Rectangle {
        id: sliderRectangle
        height: 40  * scaleFactor
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0


        Text {
            color: "#87ceeb"
            id: currentPos
            y: 8  * scaleFactor
            height: 22  * scaleFactor
            text: filling()
            anchors.right: progressSlider.left
            anchors.rightMargin: 7 * scaleFactor
            anchors.left: parent.left
            anchors.leftMargin: 7 * scaleFactor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12 * scaleFactor

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

        Slider {
            id: progressSlider
            anchors.right: parent.right
            anchors.rightMargin: 42  * scaleFactor
            anchors.left: parent.left
            anchors.leftMargin: 42  * scaleFactor
            anchors.bottom: parent.verticalCenter
            anchors.bottomMargin: -12  * scaleFactor
            anchors.top: parent.verticalCenter
            anchors.topMargin: -12 * scaleFactor

            onPressedChanged: {
                if (!pressed) {
                    mediaplayer.setCurrentPosition(value * 1000)
                    console.log("Position set to ", value)
                }
            }
        }


        Text {
            color: "#87ceeb"
            id: trackLength
            y: 8 * scaleFactor
            height: 22 * scaleFactor
            text: filling()
            anchors.right: parent.right
            anchors.rightMargin: 7 * scaleFactor
            anchors.left: progressSlider.right
            anchors.leftMargin: 7 * scaleFactor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12 * scaleFactor

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
    }

    Rectangle {
        id: buttonsRectangle
        color: "#00000000"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10 * scaleFactor
        anchors.top: sliderRectangle.bottom
        anchors.topMargin: -10 * scaleFactor

        PlayingPanelButton {
            id: playButton

            width: 60  * scaleFactor
            height: 60 * scaleFactor

            anchors.centerIn: parent

//            anchors.right: parent.right
//            anchors.rightMargin: 210 * scaleFactor
//            anchors.left: parent.left
//            anchors.leftMargin: 210 * scaleFactor
//            anchors.bottom: parent.verticalCenter
//            anchors.bottomMargin: -30 * scaleFactor
//            anchors.top: parent.verticalCenter
//            anchors.topMargin: -30 * scaleFactor

            iconSource: resourcePath + "play.svg"

            function onTouched() {
                console.log("Play touched")
                mediaplayer.playToggle()
            }
        }

        PlayingPanelButton {
            id: prevButton

            x: 164 * scaleFactor
            width: 40 * scaleFactor
            height: 40 * scaleFactor
//            anchors.top: parent.top
//            anchors.topMargin: 19 * scaleFactor
//            anchors.bottom: parent.bottom
//            anchors.bottomMargin: 18 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter

            anchors.rightMargin: 6 * scaleFactor
            anchors.right: playButton.left

            iconSource: resourcePath + "forward.svg"
            iconRotation: 180.0

            function onTouched() {
                console.log("Prev touched")
                mediaplayer.prevTrack()
            }

            function onPressAndHold() {
                //Запилить перемотку
            }
        }

        PlayingPanelButton {
            id: nextButton

//            y: -9 * scaleFactor
            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.left: playButton.right
            anchors.leftMargin: 6 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter
//            anchors.bottomMargin: 18 * scaleFactor
//            anchors.topMargin: 19 * scaleFactor
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom

            iconSource: resourcePath + "forward.svg"

            function onTouched() {
                console.log("Next touched")
                mediaplayer.nextTrack()
            }

            function onPressAndHold() {
                //Запилить перемотку
            }
        }

        PlayingPanelButton {
            id: shuffleButton

//            x: -8 * scaleFactor
//            y: -13 * scaleFactor
            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter
            anchors.right: playButton.left
            anchors.rightMargin: 80 * scaleFactor
//            anchors.bottomMargin: 18 * scaleFactor
//            anchors.topMargin: 19 * scaleFactor
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom

            iconSource: resourcePath + "shuffle.svg"

            function onTouched() {
                console.log("Shuffle touched")
                mediaplayer.shuffleToggle()
            }
        }

        PlayingPanelButton {
            id: cycleButton

//            x: 2 * scaleFactor
//            y: -2 * scaleFactor
            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter
//            anchors.bottomMargin: 18 * scaleFactor
//            anchors.topMargin: 19 * scaleFactor
            anchors.left: playButton.right
//            anchors.top: parent.top
//            anchors.bottom: parent.bottom
            anchors.leftMargin: 80 * scaleFactor

            iconSource: resourcePath + "cycle.svg"

            function onTouched() {
                console.log("Cycle touched")
                mediaplayer.cycleToggle()
            }
        }
    }

}

