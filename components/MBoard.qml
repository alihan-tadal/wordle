import  QtQuick
import Board

Rectangle {
        id: someRect
        width: Board.boardWidthInPx()
        height: Board.boardHeightInPx()
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        anchors.topMargin: 48
        color: "white"
         TableView {
            id: tableView
            anchors.fill: parent
            model: Board
            rowSpacing: 12
            columnSpacing: 12
            delegate: Rectangle {
                id: rect
                
                implicitWidth: 64
                implicitHeight: 64
                
                color: cellColor
                border {
                    width: isLocked ? 0 : 2
                    color: isEmpty ? "#d3d6da" : "#878a8c"
                }
                Text {
                    anchors.centerIn: parent
                    text: cellChar
                    font.pixelSize: 24
                    font.bold: true
                    color: isLocked ? "white" : "black"
                }
            }
    }
    }