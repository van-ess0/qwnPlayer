import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Window 2.1
import com.qwnplayer 1.0


ApplicationWindow {

    Component.onDestruction: {
        console.log("BYE")
    }

    Component.onCompleted: {
        console.log("HELLO")
        mainForm.changeTitle(qsTr("Now playing"))
        mainForm.pushToStack("HomePage.qml")

        console.log("desktop avl H:" + Screen.desktopAvailableHeight)
        console.log("desktop avl W:" + Screen.desktopAvailableWidth)

        console.log("Pixel density:" + Screen.pixelDensity.toString())
        console.log("Scale factor:" + scaleFactor.toString())
        console.log("Int scale factor:" + intScaleFactor.toString())
    }

    id: window

    property real scaleFactor: Screen.pixelDensity / 7.0
    //property real scaleFactor: 1.0
    property int intScaleFactor: Math.max(1, scaleFactor)


    visible: true
    width: 420 * scaleFactor
    height: 800 * scaleFactor

    // Settings object

    QwnSettings {
        id: settings

        Component.onDestruction: {
            settings.saveAllSettings()
        }

        Component.onCompleted: {
            settings.initialize()
        }

//Костыль ToFix
        onUrlChanged: {
            if (mainForm.stackCurrentItem().objectName === "ConnectionPage") {
                mainForm.stackCurrentItem().onUrlChanged()
            }
        }

        onUsernameChanged: {
            if (mainForm.stackCurrentItem().objectName === "ConnectionPage") {
                mainForm.stackCurrentItem().onUsernameChanged()
            }
        }

        onPasswordChanged: {
            if (mainForm.stackCurrentItem().objectName === "ConnectionPage") {
                mainForm.stackCurrentItem().onPasswordChanged()
            }
        }

        onSignalSettingsFilled: cloudClient.auth()
    }

    // Connection object

    OwnCloudClient {
        id: cloudClient
        objectName: "cloudClient"
        onSignalConnected: playingTrack.connectionState = "Connected"
    }

    // Player object

    QwnMediaPlayer {
        id: mediaplayer
        objectName: "mediaPlayer"
        onSignalPositionChanged: mainForm.onProgressChanged(progress)
        onSignalDurationChanged: mainForm.onDurationChanged(duration)
        onSignalPlayingTrackChanged: playingTrack.fillingMeta(title, artist, album)
        onSignalPlayingStateChanged: mainForm.onPlayingStateChanged(state)
        onSignalCoverChanged: playingTrack.fillingCover(coverId)
        onSignalCurrentTrackIndexChanged: playingTrack.updatePlaylistPage(index)
    }

    MainForm {
        id: mainForm
    }

    // Current Track Info

    // Do not touch this!!!
    property int currentArtistId: 0;
    property int currentAlbumId: 0;

    Item {
        id: playingTrack
        property string track: "No track name"
        property string artist: "No artist name"
        property string album: "No album name"
        property int coverId: -1

        property string connectionState: "Disconnected"

        function fillingMeta (title, artist, album){
            playingTrack.track = title
            playingTrack.artist = artist
            playingTrack.album = album
        }

        function fillingCover (coverId) {
            playingTrack.coverId = coverId
            coverChanged()
        }

        function updatePlaylistPage(index) {
            if (mainForm.stackCurrentItem().objectName === "PlaylistPage") {
                mainForm.stackCurrentItem().updateCurrentIndex(index)
            }
        }

        signal coverChanged
    }

}

