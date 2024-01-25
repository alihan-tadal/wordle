#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "userinteractor.h"
#include "gamemanager.h"
#include "boardmodel.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    GameManager *gameManager = new GameManager();
    UserInteractor *userInteractor = new UserInteractor();
    BoardModel *boardModel = new BoardModel(gameManager);

    qmlRegisterSingletonInstance("BoardModel", 1, 0, "BoardModel", boardModel);
    qmlRegisterSingletonInstance("UserInteractor", 1, 0, "UserInteractor", userInteractor);
    qmlRegisterSingletonInstance("GameManager", 1, 0, "GameManager", gameManager);
    
    const QUrl url(u"qrc:/Wordle/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
    engine.rootObjects().first()->installEventFilter(userInteractor);
    QObject::connect(userInteractor, &UserInteractor::startGameRequested, gameManager, &GameManager::onStartGameRequested);
    QObject::connect(userInteractor, &UserInteractor::exitGameRequested, gameManager, &GameManager::onExitGameRequested);


    QObject::connect(userInteractor, &UserInteractor::letterPressed, gameManager, &GameManager::onLetterPressed);
    QObject::connect(userInteractor, &UserInteractor::backspacePressed, gameManager, &GameManager::onBackspacePressed);
    QObject::connect(userInteractor, &UserInteractor::enterPressed, gameManager, &GameManager::onEnterPressed);
    
    QObject::connect(boardModel, &BoardModel::boardIsFull, gameManager, &GameManager::onBoardIsFull);

    return app.exec();
}
