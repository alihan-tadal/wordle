#include "gamemanager.h"
#include <QDebug>
#include "game.h"


/* Constructor */
GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "GameManager::GameManager() called.";
    m_hasActiveGame = false; 
}

/* Slots */
void GameManager::onStartGameRequested()
{
    qDebug() << "GameManager::onStartGameRequested() called.";
    if (!m_hasActiveGame) {
        qDebug() << "GameManager::onStartGameRequested() called. Creating new game.";
        setHasActiveGame(true);
    }
}

void GameManager::onExitGameRequested()
{
    qDebug() << "GameManager::onExitGameRequested() called.";
    if (m_hasActiveGame) {
        qDebug() << "GameManager::onExitGameRequested() called. Ending game.";
        setHasActiveGame(false);
    }
}

/* Public Methods */
void GameManager::setHasActiveGame(bool hasActiveGame)
{
    qDebug() << "GameManager::setHasActiveGame() called.";
    if (m_hasActiveGame != hasActiveGame) {
        m_hasActiveGame = hasActiveGame;
        emit hasActiveGameChanged(m_hasActiveGame);
    }
}

bool GameManager::hasActiveGame()
{
    qDebug() << "GameManager::hasActiveGame() called.";
    return m_hasActiveGame;
}




