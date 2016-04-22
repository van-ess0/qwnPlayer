import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.1 as Controls


Item {
    id: connectionPage
    objectName: "ConnectionPage"
    signal qmlSignalAuth()

//    Component.onCompleted: {
//        settings.initialize()
//        settings.onUrlChanged(onUrlChanged)
//        settings.onUsernameChanged(onUsernameChanged)
//        settings.onPasswordChanged(onPasswordChanged)
////        playingTrack.coverChanged.connect(filling)
//    }

//    settings.onUrlChanged: connectionPage.onUrlChanged()

    Column {
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            width: parent.width * 0.95
            spacing: 14 * scaleFactor

            TextField {
                id: hostInput
                onAccepted: portInput.forceActiveFocus()
                placeholderText: "owncloud host"
                KeyNavigation.tab: portInput
                text: "http://"
            }

            TextField {
                id: portInput
                onAccepted: pathInput.forceActiveFocus()
                placeholderText: "owncloud port"
                KeyNavigation.tab: pathInput
                text: "80"
            }

            TextField {
                id: pathInput
                onAccepted: nameInput.forceActiveFocus()
                placeholderText: "owncloud path to index.php"
                KeyNavigation.tab: nameInput
                text: "/owncloud/index.php"
            }

            TextField {
                id: nameInput
                onAccepted: passwordInput.forceActiveFocus()
                placeholderText: "Username"
                KeyNavigation.tab: passwordInput
            }

            TextField {
                id: passwordInput
                onAccepted: login()
                placeholderText: "Password"
                echoMode: TextInput.Password
                KeyNavigation.tab: loginButton
            }

//            Row {
//                // button
//                spacing: 20 * scaleFactor
//                width: 360 * scaleFactor
//                anchors.horizontalCenter: parent.horizontalCenter
//                anchors.alignWhenCentered: true
                TouchButton {
                    id: loginButton
                    text: "Login"
//                    baseColor: "#7a5"
                    width: parent.width
                    onClicked: login()
//                    enabled: enginioClient.authenticationState !== Enginio.Authenticating && nameInput.text.length && passwordInput.text.length
//                    KeyNavigation.tab: registerButton
                }
//                TouchButton {
//                    id: registerButton
//                    text: "Reload"
//                    onClicked: settings.initialize()
//                    width: (parent.width - parent.spacing)/2
////                    enabled: enginioClient.authenticationState !== Enginio.Authenticating && nameInput.text.length && passwordInput.text.length
//                    KeyNavigation.tab: nameInput
//                }
//            }
        }

    Text {
        id: statusText
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 70 * scaleFactor
        font.pixelSize: 18 * scaleFactor
        color: "#444"
        text: playingTrack.connectionState
    }

    function login() {

        playingTrack.connectionState = "Logging in..."

        settings.url = hostInput.text
        settings.url_port = portInput.text
        settings.url_path = pathInput.text

        settings.username = nameInput.text
        settings.password = passwordInput.text

        cloudClient.auth()

//        notificationClient.play()
    }


    function onUrlChanged() {
        console.log("on url changed")
        hostInput.text = settings.url
    }
    function onUsernameChanged() {
        console.log("on username changed")
        nameInput.text = settings.username
    }
    function onPasswordChanged() {
        console.log("on password changed")
        passwordInput.text = settings.password
    }

    function onInitFields() {
        console.log("on init fields")
        hostInput.text = settings.url
        portInput.text = settings.url_port
        pathInput.text = settings.url_path
        nameInput.text = settings.username
        passwordInput.text = settings.password
    }
}
