import QtQuick 2.15
import QtQuick.Layouts 1.15


Rectangle {
    id: chessboard
    width: 400
    height: 400

    property int squareSize: Math.min(width, height) / 8
    property string selectedSquareUci: ""

    // Signal to notify C++ when a square is clicked
    signal squareClicked(string uci)
    Grid {
        id: grid
        anchors.fill: parent
        rows: 8
        columns: 8

        Repeater {
            id: boardRepeater
            model: 64

            Rectangle {
                id: square
                width: chessboard.squareSize
                height: chessboard.squareSize
                property int piece: 13

                // Calculate file (column) and rank (row)
                readonly property int file: index % 8
                readonly property int rank: Math.floor(index / 8)


                // Store UCI notation for this square
                readonly property string uci: {
                    const fileChar = String.fromCharCode('a'.charCodeAt(0) + file);
                    return fileChar + (8 - rank);
                }

                // Alternate colors for the checkerboard pattern
                color: (file + rank) % 2 === 0 ? boardController.BLACK_SQUARE : boardController.WHITE_SQUARE

                // Visual state for selection
                Rectangle {
                    id: highlightRect
                    anchors.fill: parent
                    color: "transparent"
                    border.width: square.uci === chessboard.selectedSquareUci ? 3 : 0
                    border.color: "blue"
                    opacity: 0.5
                    z: 1
                }

                // Unicode chess piece character
                Text {
                    id: pieceText
                    anchors.centerIn: parent
                    font.pixelSize: square.width * 0.7
                    font.family: "Arial" // Or a font that has good Unicode chess symbols
                    color: "white"
                    text: ""
                    z: 2
                }

                // Make squares interactive
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        chessboard.squareClicked(square.uci);
                    }
                    z: 3
                }
            }
        }
    }
}

