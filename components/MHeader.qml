import QtQuick
import QtQuick.Controls

Rectangle {
    id: header
    width: parent.width
    height: 40
    color: window.color
    anchors.top: parent.top
    Image {
        id: wordleLogoHeader
        anchors.centerIn: parent
        width: 100
        height: 25
        source: "../assets/wordleLogoText.svg"
        smooth: true
        antialiasing: true
    }

    Image {
        id: statsIconImage
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 20
        width: 16
        height: 16
        source: "../assets/statsIcon.png"
        smooth: true
        antialiasing: true
        MouseArea {
            anchors.fill: parent
            onClicked: {
                statsPopup.open()
            }
        }
    }

    Popup {
        id: statsPopup
        width: 200
        height: 200
        modal: true
        focus: true
        anchors.centerIn: Overlay.overlay
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        enter: Transition {
                NumberAnimation { property: "opacity"; from: 0.0; to: 1.0 ; duration: 360; easing.type: Easing.Linear}
        }
        exit: Transition {
                NumberAnimation { property: "opacity"; from: 1.0; to: 0.0 ; duration: 360; easing.type: Easing.Linear}
        }
        contentItem: Rectangle {
            anchors.fill: parent
            id: statsPopupContent
            width: parent.width
            height: parent.height
            color: "#ffffff"
            Text {
                id: statsPopupText
                anchors.centerIn: parent
                text: "Stats"
                font.pixelSize: 20
                font.bold: true
            }
        }
    }

}
