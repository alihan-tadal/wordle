import QtQuick
import QtQuick.Controls
import GameManager
import UserInteractor

Popup {
        id: inGamePopup
        visible: false
        width: 160
        height: 48
        modal: false
        x: (parent.width - width) / 2
        y: 10
        opacity: 0.8
        background: Rectangle {
            id: rectBackground
            anchors.fill: parent
            radius: 12
            color: "#000000"
            opacity: 0
        }

        contentItem: Rectangle {
            id: rect
            anchors.fill: parent
            implicitWidth: 240
            implicitHeight: 64
            radius: 12
            color: "#000000"
            Text {
                id: message
                anchors.centerIn: parent
                text: qsTr("Try another word")
                font.pixelSize: 16
                font.bold: true
                color: "#ffffff"
            }
        }
        Timer {
            id: timer
            interval: 1000
            repeat: false
            running: false
            onTriggered: {
                inGamePopup.visible = false
            }
        }

        Connections {
            target: GameManager
            function onTryAnotherWord() {
                inGamePopup.visible = true
                message.text = qsTr("Not in word list!")
                timer.start()
            }
            function onGuessIsTooShort() {
                inGamePopup.visible = true
                message.text = qsTr("Word is too short!")
                timer.start()
            }
            function onGameWon() {
                inGamePopup.visible = true
                message.text = qsTr("You won!")
                inGamePopup.opacity = 1
            }
            function onGameLost(answer) {
                inGamePopup.visible = true
                inGamePopup.width = 320
                message.text = qsTr("You lost! The word was: %1").arg(answer)
                inGamePopup.opacity = 1
            }
        }
        Connections {
            target: UserInteractor
            function onExitGameRequested() {
                inGamePopup.visible = false
            }
        }
}