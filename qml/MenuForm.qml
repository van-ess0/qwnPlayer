import QtQuick 2.4

Item {
    id: menuPanel
    width: window.width
    height: window.height

    property var standartSquareSize: 60

    property var resourcePath: "qrc:/resources/images/"
    property var currentLabel: ""

    property color backgroundColor: settings.globalBackgroundColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    Column {
        id: columnMenu
        anchors {
            fill: parent
            rightMargin: 80 * scaleFactor
            leftMargin: 0
            bottomMargin: 0
            topMargin: 0
        }

        MenuButton {
            id: mainRow
            iconSource: resourcePath + "hamburgermenu.svg"
            label: qsTr("qwnPlayer")

            function onButtonClicked() {
                menuPanel.visible = false
            }
        }

        MenuButton {
            id: homeRow
            anchors.top: mainRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "home.svg"
            label: qsTr("Now playing")

            function onButtonClicked() {
                mainForm.pushToStack("HomePage.qml")
                mainForm.changeTitle(label)
                menuPanel.visible = false
            }
        }

        MenuButton {
            id: playlistRow
            anchors.top: homeRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "playlist.svg"
            label: qsTr("Playlist")

            function onButtonClicked() {
                mainForm.pushToStack("PlaylistPage.qml")
                mainForm.changeTitle(label)
                menuPanel.visible = false
            }
        }

        MenuButton {
            id: libraryRow
            anchors.top: playlistRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "library.svg"
            label: qsTr("Library")

            function onButtonClicked() {
                mainForm.pushToStack("LibraryPage.qml")
                mainForm.changeTitle(label)
                menuPanel.visible = false
            }
        }

        MenuButton {
            id: backRow
            anchors.top: libraryRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "back.svg"
            label: qsTr("Back")

            function onButtonClicked() {
                mainForm.popStack()
                menuPanel.visible = false
            }
        }

        Item {
            id: emptyRow

            anchors {
                bottom: parent.bottom
                bottomMargin: standartSquareSize * scaleFactor
                right: parent.right
                rightMargin: 0
                left: parent.left
                leftMargin: 0
                top: backRow.bottom
                topMargin: 0
            }

            Rectangle {
                id: emptyRowRectangle
                color: backgroundColor
                border.color: rectangleBorderColor
                anchors.fill: parent
            }
        }

        MenuButton {
            id: settingsRow
            anchors.top: emptyRow.bottom
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            iconSource: resourcePath + "settings.svg"
            label: qsTr("Settings")

            function onButtonClicked() {
                mainForm.pushToStack("SettingsPage.qml")
                mainForm.changeTitle(label)
                menuPanel.visible = false
            }
        }
    }
}
