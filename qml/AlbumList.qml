import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    id: albumListView
    width: parent.width
    height: parent.height
//    z: stackView.z


    LibraryView {
        id: albumView
        objectName: "AlbumView"
        model: artistModel.subModelFromId(currentArtistId)
    }
}

