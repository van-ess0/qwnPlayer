import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
//    color: "black"
    property color accentColor: settings.globalAccentColor

    Column{
        anchors.fill: parent
        spacing: 10
        //spacing: 14 * intScaleFactor

        Image {

            Component.onCompleted: {
                // Update cover on signal
                playingTrack.coverChanged.connect(filling)
            }

            id: cover_side
            anchors.horizontalCenter: parent.horizontalCenter
            width: 300 * scaleFactor
            height: 300 * scaleFactor
            source: "qrc:/resources/images/cover_sample.png"

            function filling()
            {
                if (playingTrack.coverId == -1) {
                    source = "qrc:/resources/images/cover_sample.png"
                }
                else {
                    source = "image://qwnImageProvider/" + playingTrack.coverId
                }
            }
        }

        Label {
            id: trackLabel
            anchors.horizontalCenter: parent.horizontalCenter
            text: playingTrack.track
            color: accentColor
            font.pixelSize: 28 * scaleFactor
            font.family: "Tahoma"
        }

        Label {
            id: artistLabel
            anchors.horizontalCenter: parent.horizontalCenter
            text: playingTrack.artist
            color: accentColor
            font.pixelSize: 24 * scaleFactor
            font.family: "Tahoma"

        }

        Label {
            id: albumLabel
            anchors.horizontalCenter: parent.horizontalCenter
            text: playingTrack.album
            color: accentColor
            font.pixelSize: 20 * scaleFactor
            font.family: "Tahoma"
        }
    }

    Component.onCompleted: {
//        cover_side.source: "image://qwnImageProvider/500/500/"
    }
}
