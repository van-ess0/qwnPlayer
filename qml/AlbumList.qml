import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    id: albumListView
    width: parent.width
    height: parent.height
    z: pageStack.z


    LibraryView {
        id: albumView
        objectName: "AlbumView"
        model: artistModel.subModelFromId(currentArtistId)
    }
}

