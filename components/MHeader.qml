import QtQuick

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
}
