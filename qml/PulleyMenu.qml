import QtQuick 2.0
import QtQuick.Controls 1.1

Item {
    id: pulleymenu
    anchors.top: parent.top
    property bool menu_shown: false
    property int minWidth: parent.width / 8
    property int maxWidth: parent.width / 3
    width: minWidth
    //height: parent.height

    function stateChange() {
        mamarect.width = pulleymenu.menu_shown ? minWidth : maxWidth
        pulleymenu.menu_shown = !pulleymenu.menu_shown
        mamarect.textVisibility = !mamarect.textVisibility
    }

    Loader {
        id: loadNewPage

      }

    Rectangle {
        id: mamarect
        color: "grey"
        height: parent.height
        width: parent.width
        property bool textVisibility: false

        Behavior on width {
            NumberAnimation {
                duration: 300
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
                textVisibility: mamarect.textVisibility
                iconSource: "qrc:/resources/images/hamburgermenu.svg"
                label: "Menu"

                function onTouched() {
                    console.log("Menu touched")
                    pulleyMenu.stateChange()
                }
            }

            PulleyButton {
                id: homeButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textVisibility: mamarect.textVisibility
                iconSource: "qrc:/resources/images/home.svg"
                label: "Home"
                function onTouched() {
                    console.log("Home touched")
                    if (pulleyMenu.menu_shown) {
                        pulleyMenu.stateChange()
                    }
                    stackView.clear()
                    stackView.push(Qt.resolvedUrl("HomePage.qml"))

                }
            }

            PulleyButton {
                id: playlistButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textVisibility: mamarect.textVisibility
                iconSource: "qrc:/resources/images/playlist.svg"
                label: "Playlist"
                function onTouched() {
                    console.log("Playlist touched")
                    if (pulleyMenu.menu_shown) {
                        pulleyMenu.stateChange()
                    }
                    stackView.clear()
                    stackView.push(Qt.resolvedUrl("PlaylistPage.qml"))

                }
            }

            PulleyButton {
                id: libraryButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textVisibility: mamarect.textVisibility
                iconSource: "qrc:/resources/images/library.svg"
                label: "Library"
                function onTouched() {
                    console.log("Library touched")
                    if (pulleyMenu.menu_shown) {
                        pulleyMenu.stateChange()
                    }
                    stackView.clear()
                    stackView.push(Qt.resolvedUrl("LibraryPage.qml"))

                }
            }

            PulleyButton {
                id: backButton
                width: parent.width
                minWidth: pulleymenu.minWidth
                maxWidth: pulleymenu.maxWidth
                textVisibility: mamarect.textVisibility
                iconSource: "qrc:/resources/images/previous.svg"
                label: "Back"
                function onTouched() {
                    console.log("Back touched")
                    if (pulleyMenu.menu_shown) {
                        pulleyMenu.stateChange()
                    }
                    stackView.pop()

                }
            }
        }

        PulleyButton {
            id: settingsButton
            width: parent.width
            anchors.bottom: parent.bottom
            minWidth: pulleymenu.minWidth
            maxWidth: pulleymenu.maxWidth
            textVisibility: mamarect.textVisibility

            iconSource: "qrc:/resources/images/settings.svg"
            label: "Settings"
            function onTouched() {
                console.log("Settings touched")
                if (pulleyMenu.menu_shown) {
                    pulleyMenu.stateChange()
                }
                stackView.clear()
                stackView.push(Qt.resolvedUrl("SettingsPage.qml"))

            }
        }
    }
}
