import QtQuick 2.4

Item {

    Component.onCompleted: {
        settings.menuShowPermanentChanged.connect(updateMenuShowPermanent)
    }

    function updateMenuShowPermanent() {
        console.log("menu show permanent: " + settings.menuShowPermanent)
        menuShowPermanent = settings.menuShowPermanent
        visible = menuShowPermanent
        columnMenu.width = menuShowPermanent ? minWidth : maxWidth
        textVisibility = menuShowPermanent ? false : true
    }

    function showMenu(value) {
        if (menuShowPermanent === false) {
            visible = value
        } else if (menu_shown) {
            stateChange()
        }
    }

    function stateChange() {
        columnMenu.width = menuPanel.menu_shown ?
                    minWidth :
                    maxWidth
        menuPanel.menu_shown = !menuPanel.menu_shown
        menuPanel.textVisibility = !menuPanel.textVisibility
    }

    id: menuPanel
    width: window.width
    height: window.height

    property int standartSquareSize: 60

    property string resourcePath: "qrc:/resources/images/"
    property string currentLabel: ""

    property color backgroundColor: settings.globalBackgroundColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    property bool textVisibility: menuShowPermanent ? false : true
    property bool menu_shown: false
    property bool menuShowPermanent: settings.menuShowPermanent
    property int minWidth: standartSquareSize * scaleFactor
    property int maxWidth: 340 * scaleFactor

    MouseArea {
        id: dragAreaMenu
        anchors.fill: parent
        anchors.top: parent.top
        anchors.topMargin: topRectangleMain.height
        anchors.right: parent.right
        anchors.rightMargin: menuShowPermanent ? parent.width - columnMenu.width : 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: menuShowPermanent ? bottomPanel.height : 0
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
        }

        onReleased: {

            var swipeLength = initX - mouse.x
            console.log("Released on " + mouse.x.toString())
            console.log("Swipe length " + swipeLength)

            if (swipeLength >= confHideMenuSwipe) {
                console.log("swipe hide menu")
                menuPanel.showMenu(false)
                return
            }
        }
    }

    Column {
        id: columnMenu

        width: menuShowPermanent ? minWidth : maxWidth
        height: parent.height

        Behavior on anchors.rightMargin {
            NumberAnimation {
                duration: 300
                easing.type: Easing.OutQuad
            }
        }

        MenuButton {
            id: mainRow
            iconSource: resourcePath + "hamburgermenu.svg"
            label: qsTr("qwnPlayer")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                if (menuPanel.menuShowPermanent === false) {
                    menuPanel.visible = false
                } else {
                    menuPanel.stateChange()
                }
            }
        }

        MenuButton {
            id: homeRow
            anchors.top: mainRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "home.svg"
            label: qsTr("Now playing")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                mainForm.clearStack()
                mainForm.pushToStack("HomePage.qml")
                mainForm.changeTitle(label)
                menuPanel.showMenu(false)
            }
        }

        MenuButton {
            id: playlistRow
            anchors.top: homeRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "playlist.svg"
            label: qsTr("Playlist")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                mainForm.clearStack()
                mainForm.pushToStack("PlaylistPage.qml")
                mainForm.changeTitle(label)
                menuPanel.showMenu(false)
            }
        }

        MenuButton {
            id: libraryRow
            anchors.top: playlistRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "library.svg"
            label: qsTr("Library")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                mainForm.clearStack()
                mainForm.pushToStack("LibraryPage.qml")
                mainForm.changeTitle(label)
                menuPanel.showMenu(false)
            }
        }

        MenuButton {
            id: backRow
            anchors.top: libraryRow.bottom
            anchors.topMargin: 0
            iconSource: resourcePath + "back.svg"
            label: qsTr("Back")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                mainForm.popStack()
                menuPanel.showMenu(false)
            }
        }

        Item {
            id: emptyRow

            anchors {
                bottom: parent.bottom
                bottomMargin: {
                    if (menuPanel.menuShowPermanent === true) {
                        bottomPanel.height + standartSquareSize * scaleFactor
                    } else {
                        standartSquareSize * scaleFactor
                    }
                }
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
            anchors.bottomMargin: menuPanel.menuShowPermanent ? bottomPanel.height : 0
            iconSource: resourcePath + "settings.svg"
            label: qsTr("Settings")
            textVisibility: menuPanel.textVisibility

            function onButtonClicked() {
                mainForm.clearStack()
                mainForm.pushToStack("SettingsPage.qml")
                mainForm.changeTitle(label)
                menuPanel.showMenu(false)
            }
        }
    }
}
