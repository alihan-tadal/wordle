import QtQuick
import QtQuick.Controls
import GameManager
import UserInteractor

Popup {
        id: popup
        visible: false
        anchors.centerIn: parent
        width: 400
        height: 400
        modal: true
        focus: true
        
        closePolicy: Popup.NoAutoClose	
        background: Rectangle {
            id: popupBackground
            color: "black"
            opacity: 0.5
            anchors.fill: parent
            radius: 10
        }
        contentItem: Rectangle {
            id: popupRect
            anchors.fill: parent
            radius: 10
            Text {
                id: popupText
                anchors.top: parent.top
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Stats"
                font.family: roboto_regular.name
                font.pixelSize: 30
                font.bold: true
                states: [
                    State {
                        name: "normal"
                        PropertyChanges {
                            target: popupText
                            text: "Stats"
                        }
                    },
                    State {
                        name: "gameOver"
                        when: GameManager.isGameLost || GameManager.isGameWon
                        PropertyChanges {
                            target: popupText
                            text: "AAAA"
                        }
                    }
                ]
            }
            Rectangle {
                id: controlButton
                color: "black"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
                width: 160
                height: 32
                radius: 16
                Text {
                    anchors.centerIn: parent
                    color: "#e3e3e1"

                    font.bold: true
                    text: "Exit"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log(GameManager.isGameLost, GameManager.isGameWon)
                        if (GameManager.isGameLost || GameManager.isGameWon) {
                            UserInteractor.emitExitGame()
                        }
                        popup.visible = false
                        popupText.text = "Stats"
                    }
                    
                }
            }
        }

        // add animations 
        enter: Transition {
            NumberAnimation {
                target: popupRect
                property: "opacity"
                from: 0
                to: 1
                duration: 200
            }
            NumberAnimation {
                target: popupBackground
                property: "opacity"
                from: 0
                to: 0.5
                duration: 200
            }
        }
        exit: Transition {
            NumberAnimation {
                target: popupRect
                property: "opacity"
                from: 1
                to: 0
                duration: 200
            }
            NumberAnimation {
                target: popupBackground
                property: "opacity"
                from: 0.5
                to: 0
                duration: 200
            }
        }

        Connections {
            target: GameManager
            function onGameLost() {
                popup.visible = true
            }
            function onGameWon() {
                popup.visible = true
            }
        }
}