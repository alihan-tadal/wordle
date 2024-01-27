import  QtQuick
import Qt3D.Animation
import Qt3D.Core
import QtQuick.Timeline 


Rectangle {
    id: rect
    property int indexOfThisDelegate: index
    state: getState()
    implicitWidth: 64
    implicitHeight: 64
    color: cellColor

    Text {
        id: innerText
        anchors.centerIn: parent
        text: cellChar.toUpperCase()
        font.pixelSize: 36
        font.bold: true
    }

    states: [
        State {
            name: "UE" // means unlocked and empty.
            PropertyChanges {
                target: rect;
                border.width: 2;
                border.color: "#d3d6da";
            }
            PropertyChanges {
                target: innerText;
                color: "black";
            }
        },
        State {
            name: "UF" // means unlocked and full.
            PropertyChanges {
                target: rect;
                border.width: 2;
                border.color: "#878a8c";
            }
            PropertyChanges {
                target: innerText;
                color: "black";
            }
        },
        State {
            name: "LF" // means locked and full.
            PropertyChanges {
                target: rect;
                border.width: 0;
            }
            PropertyChanges {
                target: innerText;
                color: "white";
            }
        }
    ]
    transitions: [
        // From Unlocked Empty to Unlocked Full
        Transition {
            from: "UE";
            to: "UF";
            ColorAnimation {
                    target: rect;
                    property: "border.color";
                    duration: 360;
                    easing.type: Easing.InOutQuad;
                }

            SequentialAnimation {
                PropertyAction { target: rect; property: "scale"; value: "1.1"}
                PauseAnimation { duration: 20 }
                SpringAnimation {
                    target: rect;
                    property: "scale";
                    to : 1;
                    spring: 2;
                    damping: 0.7;
                    mass: 1.5;
                    easing.type: Easing.InOutQuad;
                }
                
            }
            
        },
        // From Unlocked Full to Unlocked Empty
        Transition {
            from: "UF";
            to: "UE";
            ColorAnimation {
                    target: rect;
                    property: "border.color";
                    duration: 360;
                    easing.type: Easing.InOutQuad;
            }
        },
        // From Unlocked Full to Locked Full
        Transition {
            from: "UF";
            to: "LF";
            ColorAnimation {
                    target: innerText;
                    property: "color";
                    duration: 500;
                    easing.type: Easing.Linear;
            }
        }
    ]

    Behavior on color {
        SequentialAnimation {
            PauseAnimation { duration: 100 + 260 * getColumnFromIndex(indexOfThisDelegate)}
            ColorAnimation {
                duration: 360;
                easing.type: Easing.InOutQuad;
            }
        }
    }

    /* Javascript Part */
    function getState() {
        if (isLocked) {
            return "LF";
        } else if (isEmpty) {
            return "UE";
        } else {
            return "UF";
        }
    }

    function getColumnFromIndex(index) {
        /// I have a column-major matrix and I want to get the column from the index.
        const numRows = 6;
        const numCols = 5;
        return Math.floor(index / numRows);
    }
}


