import QtQuick 2.0

Item {
    id: pulleymenu
    property bool menu_shown: false
    property int minWidth: 40
    property int maxWidth: 200
    width: minWidth
    height: parent.height

    Rectangle {
        id: mamarect
        color: "green"
        height: parent.height
        width: minWidth
        property bool textopacity: false

        Behavior on width {
            NumberAnimation {
                duration: 400
                easing.type: Easing.OutQuad
            }
        }

        Column {
            spacing: 0
            width: parent.width
            anchors.left: parent.left

            PulleyButton {
                id: menuButton
                width: parent.width
                height: pulleymenu.minWidth
                anchors.left: parent.left
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textopacity: mamarect.textopacity
                iconSource: "qrc:/resources/images/hamburgermenu.svg"
                label: "Menu"
                colorel: "green"

                function onTouched() {
                    console.log("Menu touched")
                    mamarect.width = pulleymenu.menu_shown ? minWidth : maxWidth
                    pulleymenu.menu_shown = !pulleymenu.menu_shown;
                    mamarect.textopacity = !mamarect.textopacity;
                }
            }

            PulleyButton {
                id: homeButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textopacity: mamarect.textopacity
                iconSource: "qrc:/resources/images/home.svg"
                label: "Home"
                function onTouched() {
                    console.log("Home touched")

                }
            }

            PulleyButton {
                id: playlistButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textopacity: mamarect.textopacity
                //TODO: Find Playlist icon
                //iconSource: "qrc:/resources/images/hamburgermenu.svg"
                label: "Playlist"
                function onTouched() {
                    console.log("Playlist touched")

                }
            }

            PulleyButton {
                id: libraryButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textopacity: mamarect.textopacity
                //TODO: Find Library icon
                //iconSource: "qrc:/resources/images/home.svg"
                label: "Library"
                function onTouched() {
                    console.log("Library touched")

                }
            }
        }
        PulleyButton {
            id: settingsButton
            width: parent.width
            anchors.bottom: parent.bottom
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            textopacity: mamarect.textopacity

            iconSource: "qrc:/resources/images/settings.svg"
            label: "Settings"
            function onTouched() {
                console.log("Settings touched")

            }
        }
    }
}
