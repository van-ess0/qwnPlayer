import QtQuick 2.5
import QtQuick.Controls 1.4
import com.qwnplayer 1.0

ApplicationWindow {

    property int currentArtistId: 0;
    property int currentAlbumId: 0;

    visible: true
    width: 300
    height: 600

    QwnMediaPlayer {
        id: mediaplayer
//        onKeyGenerated: {
//            if (success) {
//                console.log("Key generation succeeded.")
//            } else {
//                console.log("Key generation failed.")
//            }
//        }
//        onTestSig: {
//            console.log("From C++")
//        }
        onSignalPositionChanged: bottomPanel.onProgressChanged(progress)
        onSignalDurationChanged: bottomPanel.onDurationChanged(duration)
    }

    //Some navigation shit O_o

    StackView {
        id: stackView
//        anchors: {
//            top: parent.top
//            bottom: bottomPanel.top
//            left: pulleyMenu.right
//            right: parent.right
//        }
        anchors.top: parent.top
        anchors.bottom: bottomPanel.top
        anchors.left: pulleyMenu.right
        anchors.right: parent.right

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

