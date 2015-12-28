import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    visible: true
    Text {
        text: qsTr("This is Home Page")
    }


    Column {


        anchors.centerIn: parent
        anchors.alignWhenCentered: true
        width: 360 * scaleFactor
        spacing: 14 * intScaleFactor

        Image {
            id: cover_side
            x: 382
            y: 19
            width: 250
            height: 250
            source: "qrc:/resources/images/cover_sample.jpg"
        }


        Rectangle {
            id: track_side
            height: 40
            Text {
                x: 95
                y: 54
                width: 190
                height: 19
                text: "Track: " + mediaplayer.currentTrack.trackTitle
                font.pointSize: 12
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.WrapAnywhere
            }
        }
        Rectangle {
            height: 40
            id: artist_side
            Text {
                x: 92
                y: 116
                width: 217
                height: 23
                text: "Artist: " + mediaplayer.currentArtist.artistName
                wrapMode: Text.WrapAnywhere
                font.pointSize: 14
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
        Rectangle {
            height: 40
            id: album_side
            Text {
                x: -20
                y: 233
                text: "Album: " + mediaplayer.currentAlbum.albumName
                wrapMode: Text.WrapAnywhere
                font.pointSize: 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

}
