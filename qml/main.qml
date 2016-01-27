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

        Component.onDestruction: {
            settings.saveAllSettings()
        }


        Component.onCompleted: {
            settings.initialize()
        }

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
                leftMargin: 20
                right: mainForm.stackRight
                rightMargin: 20
            }

            // Implements back key navigation
            focus: true
            Keys.onReleased: {
                if (event.key === Qt.Key_Back
                        && stackView.depth > 1)
                {
                    stackView.pop();
                    event.accepted = true;
                }
            }
        }

        titleLabel: menuForm.currentLabel

        MenuForm {
            id: menuForm
            function showMenu(value) {
                visible = value
            }

            visible: false
        }

        MouseArea {
            id: dragArea
            anchors.fill: parent
            property int initX: 0
            property int confBackSwipe: parent.width / 3
            property int confMenuSwipeStart: 30

            Component.onCompleted: {
                console.log("back: " + confBackSwipe)
                console.log("menu start: " + confMenuSwipeStart)
            }

            z: -1

            onPressed: {
                initX = mouse.x
                console.log("Touched on " + initX.toString())
                //mouse.accepted = false
            }

            onReleased: {

                var swipeLength = mouse.x - initX
                console.log("Released on " + mouse.x.toString())
                console.log("Swipe length " + swipeLength)

                if (initX <= confMenuSwipeStart
                        && swipeLength <= confBackSwipe) {
                    menuForm.showMenu(true)
                    console.log("swipe show menu")
                    return
                }
                else if (swipeLength >= confBackSwipe
                         && stackView.depth > 1) {
                    console.log("swipe back")
                    stackView.pop()
                    return
                }
                //mouse.accepted = true
            }
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

        function clearStack() {
            stackView.clear()
        }

        function changeTitle(value) {
            titleLabel = value
        }


    }

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

