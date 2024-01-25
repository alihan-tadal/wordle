import QtQuick 2.15

Rectangle {
        anchors.top: divider.bottom
        anchors.bottom: controls.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Column {
            anchors.centerIn: parent
            spacing: 20
            Image {
                id: wordleLogo
                anchors.horizontalCenter: parent.horizontalCenter
                width: 64
                height: 64
                source: "../assets/wordleLogo.svg"
            }
            Image {
                id: wordleLogoText
                anchors.horizontalCenter: parent.horizontalCenter
                width: 80
                height: 20
                source: "../assets/wordleLogoText.svg"
            }
            Text {
                id: welcomeText
                anchors.horizontalCenter: parent.horizontalCenter
                color: "black"
                font.bold: true
                // set alignment to center
                horizontalAlignment: Text.AlignHCenter
                text: "Get 6 chances to guess\n a 5-letter word."
                font.pixelSize: 20
            }
        }
    }    