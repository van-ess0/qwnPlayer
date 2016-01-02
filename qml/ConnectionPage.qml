import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.1 as Controls


Item {
    id: connectionPage
    objectName: "ConnectionPage"
    signal qmlSignalAuth()

//    settings.onUrlChanged: connectionPage.onUrlChanged()

    Column {
            anchors.centerIn: parent
            anchors.alignWhenCentered: true
            width: 360 * scaleFactor
            spacing: 14 * intScaleFactor

            TextField {
                id: urlInput
                onAccepted: passwordInput.forceActiveFocus()
                placeholderText: "OwnCloud URL"
                KeyNavigation.tab: nameInput
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

            Row {
                // button
                spacing: 20 * scaleFactor
                width: 360 * scaleFactor
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.alignWhenCentered: true
                TouchButton {
                    id: loginButton
                    text: "Login"
                    baseColor: "#7a5"
                    width: (parent.width - parent.spacing)/2
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
            }
        }

    Text {
        id: statusText
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 70 * scaleFactor
        font.pixelSize: 18 * scaleFactor
        color: "#444"
    }

    function login() {
        statusText.text = "Logging in..."
        settings.url = urlInput.text
        settings.username = nameInput.text
        settings.password = passwordInput.text
        cloudClient.auth()
    }


    function onUrlChanged() {
        console.log("on url changed")
        urlInput.text = settings.url
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
        urlInput.text = settings.url
        nameInput.text = settings.username
        passwordInput.text = settings.password
    }
}
