import QtQuick 2.0
import com.qwnplayer 1.0
import Sailfish.Silica 1.0

ApplicationWindow {

    id: window

    // Do not touch!!!
    property int currentArtistId: 0;
    property int currentAlbumId: 0;

    visible: true

    initialPage: Component { HomePage { } }
    cover: Qt.resolvedUrl("SFOSCover.qml")
//    allowedOrientations: Orientaiton.Portrait
//    _defaultPageOrientations: Orientation.Portrait

    QwnSettings {
        id: settings
//Костыль ToFix
        onUrlChanged: {
            if (pageStack.currentItem.objectName === "ConnectionPage") {
                pageStack.currentItem.onUrlChanged()
            }
        }

        onUsernameChanged: {
            if (pageStack.currentItem.objectName === "ConnectionPage") {
                pageStack.currentItem.onUsernameChanged()
            }
        }

        onPasswordChanged: {
            if (pageStack.currentItem.objectName === "ConnectionPage") {
                pageStack.currentItem.onPasswordChanged()
            }
        }
    }

    OwnCloudClient {
        id: cloudClient
        objectName: "cloudClient"
    }

    QwnMediaPlayer {
        id: mediaplayer
        objectName: "mediaPlayer"
        onSignalPositionChanged: bottomPanel.onProgressChanged(progress)
        onSignalDurationChanged: bottomPanel.onDurationChanged(duration)
        onSignalPlayingTrackChanged: playingTrack.fillingMeta(title, artist, album)
        onSignalPlayingStateChanged: bottomPanel.onPlayingStateChanged(state)
        onSignalCoverChanged: playingTrack.fillingCover(coverId)
        onSignalCurrentTrackIndexChanged: playingTrack.updatePlaylistPage(index)
    }

    Item {
        id: playingTrack
        property string track: "No track name"
        property string artist: "No artist name"
        property string album: "No album name"
        property int coverId: -1

        function fillingMeta (title, artist, album){
            playingTrack.track = title
            playingTrack.artist = artist
            playingTrack.album = album
        }

        function fillingCover (coverId) {
            playingTrack.coverId = coverId
        }

        function updatePlaylistPage(index) {
            if (pageStack.currentItem.objectName === "PlaylistPage") {
                pageStack.currentItem.updateCurrentIndex(index)
            }
        }
    }

}

