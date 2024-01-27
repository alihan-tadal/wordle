import  QtQuick
import BoardModel
import GameManager
Rectangle {
        id: someRect
        width: 64 * 5 + (4*tableView.rowSpacing) // 5 cells + 4 spaces
        height: 64 * 6 + (5*tableView.columnSpacing) // 6 cells + 5 spaces

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

