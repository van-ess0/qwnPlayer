import QtQuick 2.0

Item {
    Column {
        x: 10 * scaleFactor;
        y: 10 * scaleFactor
        spacing: 10 * scaleFactor
        width: parent.width - 10 * scaleFactor

        TextInfoElement {
            textLabel: "Year: " + mediaplayer.currentAlbum.albumYear
        }

        TextInfoElement {
            textLabel: "Album: " + mediaplayer.currentAlbum.albumName
        }

        TextInfoElement {
            textLabel: "Artist: " + mediaplayer.currentArtist.artistName
        }

        TextInfoElement {
            textLabel: "Type: " + mediaplayer.currentTrack.trackAudioType
        }

        TextInfoElement {
            textLabel: "Path: " + mediaplayer.currentTrack.trackServerPath
        }

        TextInfoElement {
            textLabel: "Cover: " + mediaplayer.currentAlbum.albumCover
        }
    }
}

