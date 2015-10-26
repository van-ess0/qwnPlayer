import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    id: window
    visible: true
    width: 300
    height: 500

    //Rect with labels
    Rectangle {
        id: labelrect
        //opacity: 0
        width: 0
        height: parent.height - 80
        anchors.left: window.left
        anchors.top: parent.top
        color: "black"

        Behavior on width {
            NumberAnimation {
                duration: 400
                easing.type: Easing.OutQuad
            }
        }


        Text {
            id:menuexlabel
            width: parent.width
            height: 40
            anchors.top: parent.top
            color: "white"
            font.pixelSize: 15
            text: "Menu"

        }
        Text {
            id: homeexlabel
            width: parent.width
            height: 40
            anchors.top: menuexlabel.bottom
            color: "white"
            font.pixelSize: 15
            text: "Home"

        }
        Text {
            id: playlistexlabel
            width: parent.width
            height: 40
            anchors.top: homeexlabel.bottom
            color: "white"
            font.pixelSize: 15
            text: "Playlist"

        }
        Text {
            id: libraryexlabel
            width: parent.width
            height: 40
            anchors.top: playlistexlabel.bottom
            color: "white"
            font.pixelSize: 15
            text: "Musiclibrary"

        }
        Text {
            id: settingsexlabel
            width: parent.width
            height: 40
            anchors.bottom: parent.bottom
            color: "white"
            font.pixelSize: 15
            text: "Settings"

        }

    }

    Rectangle {

        id: pulleymenu
        height: parent.height - 80
        width: 40
        anchors.left: parent.left

        color: "green"

        property bool menu_shown: false

        transform: Translate {
            id: pulleytranslate
            x: 0
            Behavior on x {
                NumberAnimation {
                    duration: 400
                    easing.type: Easing.OutQuad
                }
            }
        }

        //Hamburger menu button
        Rectangle {
            id: hamburgerbutton
            width: parent.width
            height: width
            anchors.top: parent.top
            anchors.left: parent.left
            color: parent.color

            /*Text{
                id: hamburgerbuttontext
                anchors.fill: parent
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pixelSize: parent.width
                text: qsTr("M")
            }*/
            Image {
                id: hamburgerbuttonicon
                anchors.fill: parent
                anchors.centerIn: parent
                source: "/resources/images/hamburgermenu.svg"
            }

            MouseArea {
                anchors.fill: parent
                onPressed: hamburgerbuttontext.color = "gray"
                onReleased: hamburgerbuttontext.color = "white"
                onClicked: pulleymenu.onMenu()
            }
        }

        //Home button
        Rectangle {
            id: homebutton
            width: parent.width
            height: width
            anchors.top: hamburgerbutton.bottom
            anchors.left: parent.left
            color: parent.color

            /*Text{
                id: homebuttontext
                anchors.fill: parent
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pixelSize: parent.width
                text: qsTr("H")
            }*/

            Image {
                id: homebuttonicon
                anchors.fill: parent
                anchors.centerIn: parent
                source: "/resources/images/home.svg"
            }

            MouseArea {
                anchors.fill: parent
                onPressed: homebuttontext.color = "gray"
                onReleased: homebuttontext.color = "white"
                //Go to the menu page
                //onClicked: pulleymenu.onMenu()
            }
        }

        //Playlist Button
        Rectangle {
            id: playlistbutton
            width: parent.width
            height: width
            anchors.top: homebutton.bottom
            anchors.left: parent.left
            color: parent.color

            Text{
                id: playlistbuttontext
                anchors.fill: parent
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pixelSize: parent.width
                text: qsTr("P")
            }
            /*Image {
                id: playlistbuttonicon
                anchors.fill: parent
                anchors.centerIn: parent
                source: "playlist.svg"
            }*/

            MouseArea {
                anchors.fill: parent
                onPressed: playlistbuttontext.color = "gray"
                onReleased: playlistbuttontext.color = "white"
                //Go to the library page
                //onClicked: pulleymenu.onMenu()
            }
        }

        //Library button
        Rectangle {
            id: librarybutton
            width: parent.width
            height: width
            anchors.top: playlistbutton.bottom
            anchors.left: parent.left
            color: parent.color

            Text{
                id: librarybuttontext
                anchors.fill: parent
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pixelSize: parent.width
                text: qsTr("L")
            }
            /*
            Image {
                id: librarybuttonicon
                anchors.fill: parent
                anchors.centerIn: parent
                source: "library.svg"
            }*/

            MouseArea {
                anchors.fill: parent
                onPressed: librarybuttontext.color = "gray"
                onReleased: librarybuttontext.color = "white"
                //Go to the library page
                //onClicked: pulleymenu.onMenu()
            }
        }

        //Settings button
        Rectangle {
            id: settingsbutton
            width: parent.width
            height: width
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            color: parent.color

            /*Text{
                id: settinsbuttontext
                anchors.fill: parent
                anchors.centerIn: parent
                color: "white"
                font.bold: true
                font.pixelSize: parent.width
                text: qsTr("S")
            }*/

            Image {
                id: settingsbuttonicon
                anchors.fill: parent
                anchors.centerIn: parent
                source: "/resources/images/settings.svg"
            }

            MouseArea {
                anchors.fill: parent
                onPressed: settinsbuttontext.color = "gray"
                onReleased: settinsbuttontext.color = "white"
                //Go to the settings page
                //onClicked: pulleymenu.onMenu()
            }
        }
        function onMenu() {
           pulleytranslate.x = pulleymenu.menu_shown ? 0 : 100
           labelrect.width = pulleymenu.menu_shown ? 0 : 100
           pulleymenu.menu_shown = !pulleymenu.menu_shown;
        }

    }

    Rectangle {
        id: bottomspace
        height: 80
        width: parent.width
        anchors.bottom: parent.bottom

        color: "black"

    }
}

