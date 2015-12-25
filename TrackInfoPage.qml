import QtQuick 2.0

Item {
    Column {
        x: 10; y: 10
        spacing: 10
        width: parent.width - 10
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Title: " + currentTrack.trackTitle
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Year: " + currentAlbum.albumYear
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Album: " + currentAlbum.albumName
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Artist: " + currentArtist.artistName
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Type: " + currentTrack.trackAudioType
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Path: " + currentTrack.trackServerPath
            }
        }
    }
}

