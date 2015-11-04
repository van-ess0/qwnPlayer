import QtQuick 2.5
import QtQuick.Window 2.0

Window {
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
