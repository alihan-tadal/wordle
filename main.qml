import QtQuick
import GameManager

Window {
    id: window
    width: 720
    height: 1044
    visible: true
    title: qsTr("Wordle")

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
