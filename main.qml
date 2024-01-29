import QtQuick
import QtQuick.Controls
import Stats
import GameManager
import UserInteractor

Window {
    id: window
    FontLoader {
        id: roboto_regular
        source: "fonts/roboto/Roboto-Regular.ttf"
    }
    // set default font
    
    width: 720
    height: 900
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
        id: board
        visible: GameManager.hasActiveGame ? true : false
    }

    MKeyboard {
        id: keyboard
        visible: GameManager.hasActiveGame ? true : false
    }

    MControls {
        id: controls
    }

    MStats {
        id: stats
    }

    MPopup {
        // This is for guesses that are not in the word list
        id: mpopup
    }
}
