import QtQuick 2.5
import QtQuick.Controls 1.4

ApplicationWindow {
    visible: true
    width: 300
    height: 600
    PulleyMenu {
        anchors.bottom: bottomPanel.top

    }
    BottomPanel {
        id: bottomPanel

    }
}
