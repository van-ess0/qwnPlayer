import QtQuick 2.0
import QtQuick.Controls 1.1
import QtGraphicalEffects 1.0

Item {
    id: mainForm
    width: window.width
    height: window.height
    antialiasing: false
    z: 0
    rotation: 0
    scale: 1

    property var stackTop: topRectangleMain.bottom
    property var stackBottom: bottomPanel.top
    property var stackLeft: mainForm.left
    property var stackRight: mainForm.right

    property alias titleLabel: topRow.label
    property int standartSquareSize: 60

    property color accentColor: settings.globalAccentColor
    property color backgroundColor: settings.globalBackgroundColor
    property color rectangleBorderColor: settings.globalRectangleBorderColor

    function changeTitle(value) {
        titleLabel = value
    }

    // Page Header

    Rectangle {
        id: topRectangleMain
        border.color: rectangleBorderColor
        height: standartSquareSize * scaleFactor
        color: backgroundColor
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0

        MenuButton {
            id: topRow
            iconSource: "qrc:/resources/images/hamburgermenu.svg"
            isFontUppercase: true

            function onButtonClicked() {
                mainForm.onMenuButtonClicked()
            }
        }
    }

    // Page Body

    Rectangle {
        id: midRectangleMain
        height: 600 * scaleFactor
        color: backgroundColor
        anchors.top: topRectangleMain.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 120 * scaleFactor
    }

    // Page Footer

    PlayingPanel {
        id: bottomPanel
        border.color: rectangleBorderColor
        height: 120 * scaleFactor
        color: backgroundColor
        anchors.top: midRectangleMain.bottom
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
    }

    function onProgressChanged(progress) {
        bottomPanel.onProgressChanged(progress)
    }

    function onDurationChanged(duration) {
        bottomPanel.onDurationChanged(duration)
    }

    function onPlayingStateChanged(state) {
        bottomPanel.onPlayingStateChanged(state)
    }

    // Stack view

    StackView {
        id: stackView

        anchors {
            top: mainForm.stackTop
            topMargin: 20 * scaleFactor
            bottom: mainForm.stackBottom
            bottomMargin: 20 * scaleFactor
            left: mainForm.stackLeft
            leftMargin: 20 * scaleFactor
            right: mainForm.stackRight
            rightMargin: 20 * scaleFactor
        }

        // Implements back key navigation
        focus: true
        Keys.onReleased: {
            if (event.key === Qt.Key_Back
                    && stackView.depth > 1)
            {
                stackView.pop();
                event.accepted = true;
            }
        }
    }

    function pushToStack(value) {
        stackView.push(Qt.resolvedUrl(value))
    }

    function popStack() {
        stackView.pop()
    }

    function clearStack() {
        stackView.clear()
    }

    function stackDepth() {
        return stackView.depth
    }

    function stackCurrentItem() {
        return stackView.currentItem
    }

    // Swipe Area

    MouseArea {
        id: dragArea
        anchors.fill: parent
        property int initX: 0
        property int confBackSwipe: parent.width / 2
        property int confMenuSwipeStart: 20 * scaleFactor

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

            var swipeLength = mouse.x - initX
            console.log("Released on " + mouse.x.toString())
            console.log("Swipe length " + swipeLength)

            if (initX <= confMenuSwipeStart
                    && swipeLength <= confBackSwipe) {
                menuForm.showMenu(true)
                console.log("swipe show menu")
                return
            }
            else if (swipeLength >= confBackSwipe
                     && mainForm.stackDepth() > 1) {
                console.log("swipe back")
                mainForm.popStack()
                return
            }
            //mouse.accepted = true
        }
    }

    // Left Menu Panel

    MenuForm {
        Component.onCompleted: {
            mainForm.changeTitle(currentLabel)
        }

        id: menuForm
        visible: false

        function showMenu(value) {
            visible = value
        }
    }

    function onMenuButtonClicked() {
        menuForm.showMenu(true);
    }

}
