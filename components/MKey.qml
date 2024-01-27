import  QtQuick
import BoardModel
import UserInteractor
import GameManager

// define some constant colors



Rectangle {
    property string text: "" // Text displayed on the key

    property color defaultColor: "#d3d6da"
    property color greenColor: "#6aaa64"
    property color yellowColor: "#c9b458"
    property color grayColor: "#787c7e"


    height: 64
    color: "#d3d6da"
    radius: 5

    Text {
        anchors.centerIn: parent
        text: parent.text
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            // check if letter is enter 
            if (parent.text === "\u23CE") {
                UserInteractor.enterPressed()
            } else if (parent.text === "\u232B") {
                UserInteractor.backspacePressed()
            } else {
                UserInteractor.letterPressed(parent.text.toLowerCase())
            }
        }
        // add animation on 
    }

    Connections {
        target: GameManager
        function onKeyColorUpdated(newColor, letter) {
            if (letter === text) {
                if (color === defaultColor || color === grayColor || color === yellowColor) {
                    color = newColor
                } else if (color === greenColor) {
                    color = greenColor
                }                  
            }   
        }
    }

    Behavior on color {
        ColorAnimation {
            duration: 1200
            easing.type: Easing.Linear
        }
    }
}