import QtQuick
import GameManager

Window {
    id: window
    FontLoader {
        id: roboto_regular
        source: "fonts/roboto/Roboto-Regular.ttf"
    }
    // set default font
    
    width: 720
    height: 1044
    visible: true
    title: qsTr("Wordle")
    color: GameManager.hasActiveGame ? "white":"#e3e3e1"

    MHeader {
        id: header
    }
    MDivider {
        id: divider
    }
    MWelcome {
        id: welcome
        visible: GameManager.hasActiveGame ? false : true
    }

    MBoard {
        id: saffet
        visible: GameManager.hasActiveGame ? true : false
    }
    
    MControls {
        id: controls
    }
}
