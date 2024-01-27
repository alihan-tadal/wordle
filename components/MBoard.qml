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

            rowSpacing: 8
            columnSpacing: 8
            delegate: MCell {
            }
        }

    }

