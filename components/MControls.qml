import QtQuick
import QtQuick.Controls

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
                    howToPlayPopup.open()
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

        // create popup that shows how to play
        Popup {
            id: howToPlayPopup
            modal: true
            focus: true
            anchors.centerIn: Overlay.overlay
            width: 600
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            enter: Transition {
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 ; duration: 360; easing.type: Easing.Linear}
            }
            exit: Transition {
                NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 ; duration: 360; easing.type: Easing.Linear}
            }
            contentItem: Rectangle {
                anchors.fill: parent
                Image {
                source: "../assets/howToPlay.png"
            }
            }
        }
}