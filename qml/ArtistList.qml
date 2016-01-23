import QtQuick 2.0
import Sailfish.Silica 1.0

Item {

    width: parent.width
    height: parent.height

    LibraryView {
        id: artistView
        objectName: "ArtistView"
        model: artistModel
    }
}

