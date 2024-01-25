import QtQuick
import UserInteractor
import GameManager

 Row {
        id: control_row
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        spacing: 10

        Rectangle {
            id: howToPlayButton
            width: 160
            height: 32
            radius: 16
            color: window.color
            border.color: "black"
            border.width: 2
            Text {
                anchors.centerIn: parent
                color: "black"

                font.bold: true
                text: "How to play"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    
                }
            }
        }
        Rectangle {
            id: controlButton
            color: "black"
            anchors.bottomMargin: 20
            width: 160
            height: 32
            radius: 16
            Text {
                anchors.centerIn: parent
                color: "#e3e3e1"

                font.bold: true
                text: GameManager.hasActiveGame ? "Exit" : "Play"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    GameManager.hasActiveGame ? UserInteractor.emitExitGame() : UserInteractor.emitStartGame()
                }
                
            }
        }
    }