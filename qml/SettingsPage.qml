import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    ListModel {
        id: settingsPageModel

        ListElement {
            text: "Connection"
            pageUrl: "ConnectionPage.qml"
        }

        ListElement {
            text: "About"
            pageUrl: "AboutPage.qml"
        }

        ListElement {
            text: "License"
            pageUrl: "LicensePage.qml"
        }
    }

    ListView {
        id: settingsPageView
        model: settingsPageModel

        anchors.margins: 10
        anchors.fill: parent
        spacing: 10
        clip: true

        highlight: Rectangle {
            color: "skyblue"
        }
        highlightFollowsCurrentItem: true

        delegate: LibraryElement {
            element_view: settingsPageView
            element_text: model.text
            elemet_playbutton_visible: false

            function setCurrentElement() {
                console.log("set current element")
                element_view.currentIndex = model.index
//                currentAlbumId = model.albumId
//                mediaplayer.currentAlbum = model
            }

            function onClicked() {
                setCurrentElement()
                pageStack.push(Qt.resolvedUrl(model.pageUrl))
                if (pageStack.currentItem.objectName === "ConnectionPage") {
                    console.log("init settings")
                    if (settings.is_initialized === true) {
                        pageStack.currentItem.onInitFields()
                    } else {
                        settings.initialize()
                    }

                }
            }

            function onPressAndHold() {
                setCurrentElement()
            }

        }
    }

}
