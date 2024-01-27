#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>

#include "boardmodel.h"

class GameManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool hasActiveGame READ hasActiveGame NOTIFY hasActiveGameChanged)

public:
    explicit GameManager(QObject *parent = nullptr);
    void setHasActiveGame(bool hasActiveGame);
    Q_INVOKABLE bool hasActiveGame();
    bool loadWords();
    bool checkIfWordExists(QString word);
    QString getRandomWord();
    QString evaluateGuess(QString guess);
    void updateKeyboard(QString evaluation, QString guess);


public slots:
    void onStartGameRequested();
    void onExitGameRequested();
    void onLetterPressed(QString letter);
    void onBackspacePressed();
    void onEnterPressed();
    void onBoardIsFull();

signals:
    void hasActiveGameChanged(bool hasActiveGame);
    void keyColorUpdated(QColor color, QString letter);
    void gameWon();
    void gameLost();


private:
    bool m_hasActiveGame;
    QHash<QString, int> m_words;
    BoardModel *m_boardModel;
    QString m_secretWord;
};

#endif // GAMEMANAGER_H
