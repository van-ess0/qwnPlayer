import QtQuick 2.4

Item {
    id: menuPanel
    width: window.width
    height: window.height

    property int standartSquareSize: 60

    property string resourcePath: "qrc:/resources/images/"
    property string currentLabel: ""

    property color backgroundColor: settings.globalBackgroundColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    MouseArea {
        id: dragAreaMenu
        anchors.fill: parent
        property int initX: parent.width
        property int confHideMenuSwipe: parent.width / 5

        Component.onCompleted: {
            console.log("back: " + confBackSwipe)
            console.log("menu start: " + confMenuSwipeStart)
        }

        z: -1

        onPressed: {
            initX = mouse.x
            console.log("Touched on " + initX.toString())
            //mouse.accepted = false
        }

        onReleased: {

            var swipeLength = initX - mouse.x
            console.log("Released on " + mouse.x.toString())
            console.log("Swipe length " + swipeLength)

            if (swipeLength >= confHideMenuSwipe) {
                console.log("swipe hide menu")
                menuForm.visible = false
                return
            }
            //mouse.accepted = true
        }
    }

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
                mainForm.clearStack()
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
                mainForm.clearStack()
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
                mainForm.clearStack()
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
                mainForm.clearStack()
                mainForm.pushToStack("SettingsPage.qml")
                mainForm.changeTitle(label)
                menuPanel.visible = false
            }
        }
    }
}
