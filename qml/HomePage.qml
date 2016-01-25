import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
//    color: "black"
    Column{
        anchors.fill: parent
        spacing: 10
        //spacing: 14 * intScaleFactor

        Image {
            id: cover_side
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.8
            height: width
            source: filling()

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
            color: "white"
            text: "Track: " + playingTrack.track
        }

        Label {
            id: artistLabel
            color: "white"
            text: "Artist: " + playingTrack.artist
        }

        Label {
            id: albumLabel
            color: "white"
            text: "Album: " + playingTrack.album
        }
    }

    Component.onCompleted: {
//        cover_side.source: "image://qwnImageProvider/500/500/"
    }
}
