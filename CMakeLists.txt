cmake_minimum_required(VERSION 3.16)

project(Wordle VERSION 0.1 LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "/home/alihantadal/Qt/6.6.1/gcc_64/lib/cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appWordle
    main.cpp
)

qt_add_qml_module(appWordle
    URI Wordle
    VERSION 1.0
    QML_FILES
        main.qml
        components/MHeader.qml
        components/MDivider.qml
        components/MControls.qml
        components/MWelcome.qml
        components/MBoard.qml
        components/MCell.qml
        components/MKey.qml
        components/MKeyboard.qml
        components/MPopup.qml
        components/MStats.qml
        
    SOURCES
        cell.h cell.cpp
        userinteractor.h userinteractor.cpp
        gamemanager.h gamemanager.cpp
        boardmodel.h boardmodel.cpp
        stats.h stats.cpp

    RESOURCES
        assets/wordleLogo.svg
        assets/statsIcon.png
        assets/wordleLogoText.svg
        assets/howToPlay.png
        resources/words.txt
        resources/stats.json
        fonts/roboto/Roboto-Regular.ttf
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWordle PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWordle
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWordle
    PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appWordle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
