import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Window 2.1
import com.qwnplayer 1.0


ApplicationWindow {

    Component.onCompleted: {
        mainForm.changeTitle(qsTr("Now playing"))
        mainForm.pushToStack("HomePage.qml")
        console.log("Pixel density:" + Screen.pixelDensity.toString())
        console.log("Scale factor:" + scaleFactor.toString())
        console.log("Int scale factor:" + intScaleFactor.toString())
    }

    id: window

    property real intScaleFactor: Screen.pixelDensity / 9.0
    //property real scaleFactor: 1.0
    property int scaleFactor: Math.max(1, intScaleFactor)

    // Do not touch!!!
    property int currentArtistId: 0;
    property int currentAlbumId: 0;

    visible: true
    width: 420 * scaleFactor
    height: 800 * scaleFactor

    QwnSettings {
        id: settings
//Костыль ToFix
        onUrlChanged: {
            if (stackView.currentItem.objectName === "ConnectionPage") {
                stackView.currentItem.onUrlChanged()
            }
        }

        onUsernameChanged: {
            if (stackView.currentItem.objectName === "ConnectionPage") {
                stackView.currentItem.onUsernameChanged()
            }
        }

        onPasswordChanged: {
            if (stackView.currentItem.objectName === "ConnectionPage") {
                stackView.currentItem.onPasswordChanged()
            }
        }

        onSignalSettingsFilled: cloudClient.auth()
    }

    OwnCloudClient {
        id: cloudClient
        objectName: "cloudClient"
        onSignalConnected: playingTrack.connectionState = "Connected"
    }

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

    /*

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
    }

    */

    MainForm {
        id: mainForm


        StackView {
            id: stackView
            anchors {
                top: mainForm.stackTop
                topMargin: 20
                bottom: mainForm.stackBottom
                bottomMargin: 20
                left: mainForm.stackLeft
                leftMargin: 10
                right: mainForm.stackRight
                rightMargin: 10
            }

            // Implements back key navigation
            focus: true
            Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                                 stackView.pop();
                                 event.accepted = true;
                             }
//            initialItem: Qt.resolvedUrl("HomePage.qml")
        }

        titleLabel: menuForm.currentLabel

        MenuForm {
            id: menuForm
            function showMenu(value) {
                visible = value
            }

            visible: false
        }

        function onMenuButtonClicked() {
            console.log("on menu ");
            menuForm.showMenu(true);
        }

        function pushToStack(value) {
            stackView.push(Qt.resolvedUrl(value))
        }

        function popStack() {
            stackView.pop()
        }

        function changeTitle(value) {
            titleLabel = value
        }


    }



    /*

    PulleyMenu {
        id: pulleyMenu
        anchors.bottom: bottomPanel.visible ? bottomPanel.top: parent.bottom
    }

    BottomPanel {
        id: bottomPanel

    }

    */



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
        }

        function updatePlaylistPage(index) {
            if (stackView.currentItem.objectName === "PlaylistPage") {
                stackView.currentItem.updateCurrentIndex(index)
            }
        }
    }

}

