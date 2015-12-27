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
                text: "Title: " + mediaplayer.currentTrack.trackTitle
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Year: " + mediaplayer.currentAlbum.albumYear
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Album: " + mediaplayer.currentAlbum.albumName
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Artist: " + mediaplayer.currentArtist.artistName
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Type: " + mediaplayer.currentTrack.trackAudioType
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Path: " + mediaplayer.currentTrack.trackServerPath
            }
        }
        Rectangle {
            width: parent.width
            height: 20
            Text {
                text: "Cover: " + mediaplayer.currentAlbum.albumCover
            }
        }
    }
}

