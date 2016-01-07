import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

    width: parent.width
    height: parent.height

    LibraryView {
        id: artistView
        objectName: "ArtistView"
        model: artistModel
    }
}

