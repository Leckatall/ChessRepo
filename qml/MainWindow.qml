
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15


ApplicationWindow {
    id: mainWindow
    visible: true
    width: 1200
    height: 800
    title: "ChessRepo"

    // Menu bar
    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "Exit"
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: "View"
        }
    }


    // Status bar
    footer: ToolBar {
        RowLayout {
            anchors.fill: parent
            Label {
                text: "Ready"
                Layout.alignment: Qt.AlignLeft
            }
        }
    }

    // Chess canvas (placeholder for your chess board component)
    ChessBoard {
        id: chess_board
        anchors.centerIn: parent
        width: parent.height * 0.8
        height: parent.height * 0.8
        color: "lightgray"

        Text {
            text: "Chess Board Display"
            anchors.centerIn: parent
            font.pixelSize: 24
        }
    }
}



