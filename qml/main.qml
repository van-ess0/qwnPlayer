import QtQuick 2.5
import QtQuick.Controls 1.4
import com.qwnplayer 1.0
import Enginio 1.0

ApplicationWindow {

    id: window

    property real scaleFactor: 1.0
    property int intScaleFactor: Math.max(1, scaleFactor)

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
        onSignalPositionChanged: bottomPanel.onProgressChanged(progress)
        onSignalDurationChanged: bottomPanel.onDurationChanged(duration)
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

}

