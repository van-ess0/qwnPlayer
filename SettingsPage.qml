import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 300
    height: 600

    PulleyMenu {
        anchors.bottom: bottomPanel.visible ? bottomPanel.top: parent.bottom

    }

    BottomPanel {
        id: bottomPanel

    }

    Text {
        id: settingsText
        text: qsTr("This is settings Page")
    }

}
