#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "board.h"
#include "userinteractor.h"
#include "gamemanager.h"
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    
    Board *board = new Board();
    UserInteractor *userInteractor = new UserInteractor(board);
    GameManager *gameManager = new GameManager();

    qmlRegisterSingletonInstance("Board", 1, 0, "Board", board);
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
    return app.exec();
}