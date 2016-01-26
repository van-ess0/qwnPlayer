import QtQuick 2.0

Item {
    Column {
        x: 10 * scaleFactor;
        y: 10 * scaleFactor
        spacing: 10 * scaleFactor
        width: parent.width - 10 * scaleFactor
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Title: " + mediaplayer.currentTrack.trackTitle
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Year: " + mediaplayer.currentAlbum.albumYear
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Album: " + mediaplayer.currentAlbum.albumName
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Artist: " + mediaplayer.currentArtist.artistName
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Type: " + mediaplayer.currentTrack.trackAudioType
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Path: " + mediaplayer.currentTrack.trackServerPath
            }
        }
        Rectangle {
            width: parent.width
            height: 20 * scaleFactor
            Text {
                text: "Cover: " + mediaplayer.currentAlbum.albumCover
            }
        }
    }
}

