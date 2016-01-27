import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1

Rectangle {

    color: "#00000000"

    property var resourcePath: "qrc:/resources/images/"

    property color accentColor: settings.globalAccentColor
    property color rectangleColor: settings.globalRectangleColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

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
            Component.onCompleted: {
                text = progressSlider.calcTime(progressSlider.value)
            }

            color: accentColor
            id: currentPos
            y: 8  * scaleFactor
            height: 22  * scaleFactor
            anchors.right: progressSlider.left
            anchors.rightMargin: 7 * scaleFactor
            anchors.left: parent.left
            anchors.leftMargin: 7 * scaleFactor
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 12 * scaleFactor
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

            style: SliderStyle {
                groove: Rectangle {
                    implicitWidth: parent.width
                    implicitHeight: 8 * scaleFactor
                    color: rectangleColor
                    radius: 8
                    border.color: rectangleBorderColor

                    Rectangle {
                        height: parent.height
                        width: styleData.handlePosition
                        radius: parent.radius
                        color: accentColor
                        border.color: rectangleBorderColor
                    }
                }
                handle: Rectangle {
                    anchors.centerIn: parent
                    color: control.pressed ? Qt.lighter(accentColor, 1.5) : Qt.lighter(accentColor, 1.2)
                    border.color: rectangleBorderColor
                    border.width: 1
                    implicitWidth: 34 * scaleFactor
                    implicitHeight: 34 * scaleFactor
                    radius: 50
                }
            }

            function calcTime(valueToCalc) {

                var seconds = ""
                var nseconds = (valueToCalc % 60)

                if (nseconds < 10) {
                    seconds = "0" + Math.round(nseconds).toString()
                }
                else {
                    seconds = Math.round(nseconds).toString()
                }

                var minutes = ((valueToCalc - nseconds) / 60).toString();

                return (qsTr(minutes + ":" + seconds))
            }

            onValueChanged: {
                currentPos.text = calcTime(value)
            }

            onMaximumValueChanged: {
                trackLength.text = calcTime(maximumValue)
            }

            onPressedChanged: {
                if (!pressed) {
                    mediaplayer.setCurrentPosition(value * 1000)
                    console.log("Position set to ", value)
                }
            }
        }


        Text {
            Component.onCompleted: {
                text = progressSlider.calcTime(progressSlider.maximumValue)
            }

            color: accentColor
            id: trackLength
            y: 8 * scaleFactor
            height: 22 * scaleFactor

            anchors.right: parent.right
            anchors.rightMargin: 7 * scaleFactor
            anchors.left: progressSlider.right
            anchors.leftMargin: 7 * scaleFactor
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12 * scaleFactor
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

            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.left: playButton.right
            anchors.leftMargin: 6 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter

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
            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter
            anchors.right: playButton.left
            anchors.rightMargin: 80 * scaleFactor

            iconSource: resourcePath + "shuffle.svg"

            function onTouched() {
                console.log("Shuffle touched")
                mediaplayer.shuffleToggle()
            }
        }

        PlayingPanelButton {
            id: cycleButton

            width: 40 * scaleFactor
            height: 40 * scaleFactor
            anchors.verticalCenter: playButton.verticalCenter
            anchors.left: playButton.right
            anchors.leftMargin: 80 * scaleFactor

            iconSource: resourcePath + "cycle.svg"

            function onTouched() {
                console.log("Cycle touched")
                mediaplayer.cycleToggle()
            }
        }
    }

}

