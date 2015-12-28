import QtQuick 2.5
import QtQuick.Controls 1.4

Item {
    Text {
        text: qsTr("This is Home Page")
    }

    Column{
        anchors.fill: parent
        spacing: 10
        //spacing: 14 * intScaleFactor

        Image {
            id: cover_side
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width * 0.8
            height: width
            source: "qrc:/resources/images/cover_sample.jpg"
        }

        Label {
            id: trackLabel
            text: "Track: " + mediaplayer.currentTrack.trackTitle
        }

        Label {
            id: artistLabel
            text: "Artist: " + mediaplayer.currentArtist.artistName
        }

        Label {
            id: albumLabel
            text: "Album: " + mediaplayer.currentAlbum.albumName
        }
    }

}
