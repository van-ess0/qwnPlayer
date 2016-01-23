import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Home")
                onClicked: pageStack.push(Qt.resolvedUrl("HomePage.qml"))
            }
            MenuItem {
                text: qsTr("Library")
                onClicked: pageStack.push(Qt.resolvedUrl("LibraryPage.qml"))
            }
            MenuItem {
                text: qsTr("Playlist")
                onClicked: pageStack.push(Qt.resolvedUrl("PlaylistPage.qml"))
            }
            MenuItem {
                text: qsTr("SettingsPage")
                onClicked: pageStack.push(Qt.resolvedUrl("HomePage.qml"))
            }
        }

        Column {
            anchors.fill: parent
            spacing: 10
            //spacing: 14 * intScaleFactor

            Image {
                id: cover_side
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width * 0.8
                height: width
                source: filling()

                function filling()
                {
                    if (playingTrack.coverId == -1) {
                        source = "qrc:/resources/images/cover_sample.jpg"
                    }
                    else {
                        source = "image://qwnImageProvider/" + playingTrack.coverId
                    }
                }
            }

            Label {
                id: trackLabel
                text: "Track: " + playingTrack.track
            }

            Label {
                id: artistLabel
                text: "Artist: " + playingTrack.artist
            }

            Label {
                id: albumLabel
                text: "Album: " + playingTrack.album
            }
        }

        Component.onCompleted: {
            //        cover_side.source: "image://qwnImageProvider/500/500/"
        }
    }
}
