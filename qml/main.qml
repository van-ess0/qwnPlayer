import QtQuick 2.0
import QtQuick.Controls 1.1
import com.qwnplayer 1.0

ApplicationWindow {

    id: window

    property real scaleFactor: 1.0
    property int intScaleFactor: Math.max(1, scaleFactor)

    // Do not touch!!!
    property int currentArtistId: 0;
    property int currentAlbumId: 0;

    visible: true
    width: 400 * scaleFactor
    height: 640 * scaleFactor

    QwnSettings {
        id: settings

        onUrlChanged: {
            if (stackView.currentItem.objectName == "ConnectionPage") {
                stackView.currentItem.onUrlChanged()
            }
        }

        onUsernameChanged: {
            if (stackView.currentItem.objectName == "ConnectionPage") {
                stackView.currentItem.onUsernameChanged()
            }
        }

        onPasswordChanged: {
            if (stackView.currentItem.objectName == "ConnectionPage") {
                stackView.currentItem.onPasswordChanged()
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
        onSignalCoverChanged: playingTrack.fillingCover(coverId)
    }

    StackView {
        id: stackView
        anchors {
            top: parent.top
            bottom: bottomPanel.top
            left: pulleyMenu.right
            right: parent.right
        }

        // Implements back key navigation
        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                             stackView.pop();
                             event.accepted = true;
                         }
        initialItem: Qt.resolvedUrl("HomePage.qml")
    }

    PulleyMenu {
        id: pulleyMenu
        anchors.bottom: bottomPanel.visible ? bottomPanel.top: parent.bottom
    }

    BottomPanel {
        id: bottomPanel

    }

    Item {
        id: playingTrack
        property string track: "value"
        property string artist: "value"
        property string album: "value"
        property int coverId: 17

        function fillingMeta (title, artist, album){
            playingTrack.track = title
            playingTrack.artist = artist
            playingTrack.album = album
        }

        function fillingCover (coverId) {
            playingTrack.coverId = coverId
        }
    }

}

