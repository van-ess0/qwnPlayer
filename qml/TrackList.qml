import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: trackListView
    width: parent.width
    height: parent.height
    z: pageStack.z

    LibraryView {
        id: trackView
        objectName: "TrackView"
        model: artistModel.subModelFromId(currentArtistId).subModelFromId(currentAlbumId)
    }
}
