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
            text: "Theme preferences"
            pageUrl: "ThemeSettingPage.qml"
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

    LibraryView {
        id: settingsView
        objectName: "SettingsView"
        model: settingsPageModel
    }

}
