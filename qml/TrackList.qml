import QtQuick 2.0

Item {
    id: trackListView
    width: parent.width
    height: parent.height
    z: stackView.z

    LibraryView {
        id: trackView
        objectName: "TrackView"
        model: artistModel.subModelFromId(currentArtistId).subModelFromId(currentAlbumId)
    }
}

