#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>

#include "stats.h"
#include "boardmodel.h"

class GameManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool hasActiveGame READ hasActiveGame NOTIFY hasActiveGameChanged)
    Q_PROPERTY(bool isGameWon READ isGameWon NOTIFY gameWon)
    Q_PROPERTY(bool isGameLost READ isGameLost NOTIFY gameLost)

public:
    explicit GameManager(QObject *parent = nullptr);
    void setHasActiveGame(bool hasActiveGame);
    Q_INVOKABLE bool hasActiveGame();
    Q_INVOKABLE bool isGameWon();
    Q_INVOKABLE bool isGameLost();
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
    // Emitted when game is started or exited.
    void hasActiveGameChanged(bool hasActiveGame);
    
    // After enter pressed and word is evaluated, if word exists in dictionary, this signal tells keyboard which letters to update to which color.
    void keyColorUpdated(QColor color, QString letter);

    // Emitted when game is won.
    void gameWon();

    // Emitted when game is lost. Secret word is sent to QML to show it to user.
    void gameLost(QString secretWord);

    // After enter pressed and word is evaluated, these signals are emitted if word is not found in dictionary.
    void tryAnotherWord();

    // After enter pressed and word is evaluated, these signals are emitted if word is not valid.
    void guessIsTooShort();


private:
    // Used to check if game is active. If game is active, user can play. Main.qml heavily depends on this.
    bool m_hasActiveGame;
    
    // Used to check if game is won. If all letters are green, game is won.
    bool m_isGameWon = false;

    // Used to check if game is lost. If board is full and no word is found, game is lost.
    bool m_isGameLost = false;
    
    int m_numGuesses = 0;

    // This is where all the words are stored. Used hashtable to faster check if word exists.
    QHash<QString, int> m_words;
    

    // Where the secret word for each session is stored. When game ended, it will be empty string.
    QString m_secretWord; 
    
    // Important when updating keyboard to not update green back to yellow.
    QList<QString> m_greens; 

    // Reference to the board model. GameManager communicates with board model through this.
    BoardModel *m_boardModel;

    // Reference to stats object. GameManager communicates with stats object through this.
    Stats *m_stats;
};

#endif // GAMEMANAGER_H
