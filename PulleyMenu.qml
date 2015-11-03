import QtQuick 2.0
Item{
    id: pulleymenu
    property bool menu_shown: false
    property int minWidth: 40
    property int maxWidth: 200
    width: minWidth
    height: parent.height

    Column {
        spacing: 0
        width: parent.width
        anchors.left: parent.left

        PulleyButton {
            id: menuButton
            width: parent.width
            height: pulleymenu.minWidth
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            iconSource: "qrc:/resources/images/hamburgermenu.svg"
            label: "Menu"

            function onTouched() {
                console.log("Menu touched")
                pulleymenu.width = pulleymenu.menu_shown ? minWidth : maxWidth
                pulleymenu.menu_shown = !pulleymenu.menu_shown;
            }
        }

        PulleyButton {
            id: homeButton
            width: parent.width
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            iconSource: "qrc:/resources/images/home.svg"
            label: "Home"
            function onTouched() {

            }
        }

        PulleyButton {
            id: playlistButton
            width: parent.width
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            //TODO: Find Playlist icon
            //iconSource: "qrc:/resources/images/hamburgermenu.svg"
            label: "Playlist"
            function onTouched() {

            }
        }

        PulleyButton {
            id: libraryButton
            width: parent.width
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            //TODO: Find Library icon
            //iconSource: "qrc:/resources/images/home.svg"
            label: "Library"
            function onTouched() {

            }
        }
    }
}
