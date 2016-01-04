import QtQuick 2.0
import QtQuick.Controls 1.1

Item {

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

        delegate: Item {
            id: library_element
            property var element_view: settingsPageView
            property string element_text: model.text

            width: element_view.width
            height: 40

            function setCurrentElement() {
                console.log("set current element")
                element_view.currentIndex = model.index
//                currentAlbumId = model.albumId
//                mediaplayer.currentAlbum = model
            }

//            function onPlayTouched() {
//                setCurrentElement()
//            }

            function onPressAndHold() {
                setCurrentElement()
            }

//            function onClicked() {
//                setCurrentElement()
//            }

            function onClicked() {
                setCurrentElement()
                stackView.push(Qt.resolvedUrl(model.pageUrl))
                if (stackView.currentItem.objectName === "ConnectionPage") {
                    console.log("init settings")
                    if (settings.is_initialized === true) {
                        stackView.currentItem.onInitFields()
                    } else {
                        settings.initialize()
                    }

                }
            }

            Rectangle {
                anchors.margins: 5
                anchors.fill: parent

                border {
                    color: "black"
                    width: 1
                }

//                BottomPanelButton {
//                    id: playbutton_element
//                    objectName: "playbutton"
//                    anchors.left: parent
//                    anchors.verticalCenter: parent.verticalCenter
//                    width: 20
//                    height: 20
//                    iconSource: "qrc:/resources/images/play.svg"
//                    function onTouched() {
//                        library_element.onPlayTouched()
//                    }
//                }

                Text {
                    id: text_element
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent
                    anchors.margins: 5
                    renderType: Text.NativeRendering
                    text: element_text
                }

                MouseArea {
                    id: mouse_area_element
                    height: 40
                    anchors.fill: parent
                    onPressAndHold: library_element.onPressAndHold()
                    onClicked: library_element.onClicked()
                    onDoubleClicked: library_element.onDoubleClicked()
                }
            }

        }
    }

}
