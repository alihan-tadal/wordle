import  QtQuick
import BoardModel
import GameManager
Rectangle {
        id: keyboard
        width: board.width * (8/6)
        height: board.height * (0.8)
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: board.bottom
        anchors.topMargin: 24

        Row {
            id: row1
            // calculate width
            width: 10 * 36 + 9 * 8 // 10 keys, 36 width, 9 spacing
            spacing: 8
            anchors.horizontalCenter: parent.horizontalCenter
            MKey { text: "Q"; width: 36}
            MKey { text: "W"; width: 36}
            MKey { text: "E"; width: 36}
            MKey { text: "R"; width: 36}
            MKey { text: "T"; width: 36}
            MKey { text: "Y"; width: 36}
            MKey { text: "U"; width: 36}
            MKey { text: "I"; width: 36}
            MKey { text: "O"; width: 36}
            MKey { text: "P"; width: 36}
        }
        Row {
            id: row2
            // calculate width
            width: 9 * 36 + 8 * 8 // 9 keys, 36 width, 8 spacing
            spacing: 8
            anchors.top: row1.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: parent.horizontalCenter
            MKey { text: "A"; width: 36}
            MKey { text: "S"; width: 36}
            MKey { text: "D"; width: 36}
            MKey { text: "F"; width: 36}
            MKey { text: "G"; width: 36}
            MKey { text: "H"; width: 36}
            MKey { text: "J"; width: 36}
            MKey { text: "K"; width: 36}
            MKey { text: "L"; width: 36}
        }

        Row {
            id: row3
            // calculate width
            width: 7 * 36 + 2 * 48 + 8 * 8 // 7 keys, 36 width, 2 keys 48 width, 8 spacing
            spacing: 8
            anchors.top: row2.bottom
            anchors.topMargin: 12
            anchors.horizontalCenter: parent.horizontalCenter
            MKey { text: "\u23CE"; width: 48}
            MKey { text: "Z"; width: 36}
            MKey { text: "X"; width: 36}
            MKey { text: "C"; width: 36}
            MKey { text: "V"; width: 36}
            MKey { text: "B"; width: 36}
            MKey { text: "N"; width: 36}
            MKey { text: "M"; width: 36}
            MKey { text: "\u232B"; width: 48}
        }
}

