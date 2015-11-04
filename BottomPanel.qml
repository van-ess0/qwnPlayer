import QtQuick 2.5

Item {

    height: 100
    width: parent.width
    anchors.bottom: parent.bottom

    Rectangle {
        anchors.fill: parent
        color: "green"

        BottomPanelButton {
            id: playbutton
            anchors.centerIn: parent
            width: 40
            height: 40
            iconSource: "qrc:/resources/images/play.svg"

            function onTouched() {
                console.log("Play touched")

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

            }
        }

    }
}

