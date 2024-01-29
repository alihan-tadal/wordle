import QtQuick
import QtQuick.Controls
import Stats
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
                anchors.left: parent.left
                anchors.leftMargin: 20
                text: "STATISTICS"
                font.family: roboto_regular.name
                font.pixelSize: 18
                font.bold: true
                states: [
                    State {
                        name: "normal"
                        PropertyChanges {
                            target: popupText
                            text: "STATISTICS"
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
                id: content 
                anchors.top: popupText.bottom
                anchors.topMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                // width: parent.width
                // height: 200
                Row {
                    id: row1
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Column {
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: Stats.gamePlays
                            font.family: roboto_regular.name
                            font.pixelSize: 32
                            font.bold: true
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Played"
                            font.family: roboto_regular.name
                            font.pixelSize: 16
                        }
                    }
                    Column {
                        Text {
                            property int winPercentage: Stats.gamePlays > 0 ? Stats.gameWins / Stats.gamePlays * 100 : 0
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: winPercentage
                            font.family: roboto_regular.name
                            font.pixelSize: 32
                            font.bold: true
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Win %"
                            font.family: roboto_regular.name
                            font.pixelSize: 16
                        }
                    }
                    Column {
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: Stats.streak
                            font.family: roboto_regular.name
                            font.pixelSize: 32
                            font.bold: true
                            
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Current\nStreak"
                            font.family: roboto_regular.name
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    Column {
                        id: column4
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: Stats.maxStreak
                            font.family: roboto_regular.name
                            font.pixelSize: 32
                            font.bold: true
                            
                        }
                        Text {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: "Max\nStreak"
                            font.family: roboto_regular.name
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }          
            }
            
            Text {
                text: "GUESS DISTRIBUTION"
                anchors.bottom : guessDistribution.top
                anchors.bottomMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
            }
            ListView {
                id: guessDistribution
                anchors.bottom: controlButton.top
                anchors.bottomMargin: 20
                anchors.left: parent.left
                anchors.leftMargin: 20
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                height: 6 * 18 + 5 * 2
                model: Stats.winDistribution
                delegate: Row {
                    property int index: model.index
                    height: 18
                    spacing: 8
                    Text {
                        text: index + 1
                        font.family: roboto_regular.name
                        font.pixelSize: 16
                        font.bold: true
                    }
                    Rectangle {
                        color: "#6aaa64"
                        anchors.topMargin: 16
                        width: 200 * Stats.winDistribution[index] / Stats.gameWins
                        height: 16
                        Text {
                            anchors.right: parent.right
                            anchors.rightMargin: 2
                            text: Stats.winDistribution[index] == 0 ? "" : Stats.winDistribution[index]
                            font.family: roboto_regular.name
                            font.pixelSize: 14
                            color: "white"
                        }
                        Behavior on width {
                            NumberAnimation {
                                duration: 4000
                            }
                        }
                    }
                }
            }

            Text {
                text: "Reset Statistics"
                anchors.bottom : controlButton.top
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottomMargin: 7
                font.pixelSize: 14
                // add text decoration underline
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Stats.resetStats()
                    }
                }
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
                        popupText.text = "STATISTICS"
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