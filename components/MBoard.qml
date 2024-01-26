import  QtQuick
import BoardModel
import GameManager
Rectangle {
        id: someRect
        width: 400
        height: 400
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: header.bottom
        anchors.topMargin: 48
        color: GameManager.hasActiveGame ? "white" : "#e3e3e1"
         TableView {
            id: tableView
            anchors.fill: parent
            model: BoardModel 

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
                    text: cellChar.toUpperCase()
                    font.pixelSize: 24
                    font.bold: true
                    color: isLocked ? "white" : "black"
                }


            }
    }
    // make transition animation when visible is changed
    Behavior on visible {
        // if visible is true, then make animation
        SequentialAnimation {
            NumberAnimation {
                target: someRect
                property: "opacity"
                from: 0
                to: 1
                duration: 500
            }
        }

        // if visible is false, then make animation
        SequentialAnimation {
            NumberAnimation {
                target: someRect
                property: "opacity"
                from: 1
                to: 0
                duration: 500
            }
        }
    }
}
