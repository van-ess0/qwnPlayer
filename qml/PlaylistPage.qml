import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    id: playlistPage
    objectName: "PlaylistPage"

    width: parent.width
    height: parent.height

    LibraryView {
        id: playlistView
        objectName: "PlaylistView"
        model: currentPlaylist
    }

    function updateCurrentIndex(index) {
        playlistView.updateCurrentIndex(index)
    }

    Component.onCompleted: {
        updateCurrentIndex(mediaplayer.currentTrackIndex)
    }
}
