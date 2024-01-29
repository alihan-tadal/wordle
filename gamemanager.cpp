#include <QDebug>
#include <QFile>
#include <QDir>
#include <QRandomGenerator>

#include "gamemanager.h"
#include "boardmodel.h"

/* Constructor */
GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "GameManager::GameManager() called.";
    m_hasActiveGame = false;
    // try to load words from file
    if (!loadWords())
    {
        qDebug() << "GameManager::GameManager() called. Failed to load words.";
    }
}

/* Slots */
void GameManager::onStartGameRequested()
{
    qDebug() << "GameManager::onStartGameRequested() called.";
    if (!m_hasActiveGame)
    {
        qDebug() << "GameManager::onStartGameRequested() called. Creating new game.";
        setHasActiveGame(true);
        m_boardModel = qobject_cast<BoardModel *>(children().first());
        // write row count
        qDebug() << "GameManager::onStartGameRequested() called with row count: " << m_boardModel->rowCount(QModelIndex());
        m_boardModel->resetBoard();
        m_secretWord = getRandomWord();
        qDebug() << "GameManager::onStartGameRequested() called. Secret word is: " << m_secretWord;
    }
}

void GameManager::onExitGameRequested()
{
    qDebug() << "GameManager::onExitGameRequested() called.";
    if (m_hasActiveGame)
    {
        qDebug() << "GameManager::onExitGameRequested() called. Ending game.";
        setHasActiveGame(false);
        m_boardModel->resetBoard();
        m_secretWord = "";
        m_isGameWon = false;
        m_isGameLost = false;
        m_greens.clear();
    }
}

void GameManager::onLetterPressed(QString letter)
{
    qDebug() << "GameManager::onLetterPressed() called.";
    if (m_hasActiveGame && (!m_isGameWon && !m_isGameLost)) // after game is won or lost, no more letters can be added
    {
        qDebug() << "GameManager::onLetterPressed() called. Adding letter to game.";
        m_boardModel->insertLetter(letter);
    }
}

void GameManager::onBackspacePressed()
{
    qDebug() << "GameManager::onBackspacePressed() called.";
    if (m_hasActiveGame && (!m_isGameWon && !m_isGameLost)) // after game is won or lost, no more letters can be removed
    {
        qDebug() << "GameManager::onBackspacePressed() called. Removing letter from game.";
        m_boardModel->removeLetter();
    }
}

void GameManager::onEnterPressed()
{
    qDebug() << "GameManager::onEnterPressed() called.";
    if (m_hasActiveGame && (!m_isGameWon && !m_isGameLost)) // after game is won or lost, no more checks can be made
    {
        qDebug() << "GameManager::onEnterPressed() called. Checking if word exists.";
        QString guess = m_boardModel->getGuess();
        qDebug() << "GameManager::onEnterPressed() called. Guess is: " << guess;
        // check guess length is less than WORD_LENGTH
        if (guess.length() < WORD_LENGTH)
        {
            qDebug() << "GameManager::onEnterPressed() called. Guess is too short.";
            emit guessIsTooShort();
            return;
        }
        if (checkIfWordExists(guess))
        {
            qDebug() << "Word exists. Evaluating...";
            QString evaluation = evaluateGuess(guess);
            updateKeyboard(evaluation, guess);
            m_boardModel->lockGuess(evaluation);
            if (evaluation == "GGGGG")
            {
                qDebug() << "You won!";
                emit gameWon();
                m_isGameWon = true;
            }
        }
        else
        {
            qDebug() << "Word does not exist. Try Again";
            emit tryAnotherWord();
        }
    }
}

void GameManager::onBoardIsFull()
{
    qDebug() << "GameManager::onBoardIsFull() called. Game lost.";
    emit gameLost(m_secretWord);
    m_isGameLost = true;
}

/* Public Methods */
void GameManager::setHasActiveGame(bool hasActiveGame)
{
    qDebug() << "GameManager::setHasActiveGame() called.";
    if (m_hasActiveGame != hasActiveGame)
    {
        m_hasActiveGame = hasActiveGame;
        emit hasActiveGameChanged(m_hasActiveGame);
    }
}

bool GameManager::hasActiveGame()
{
    qDebug() << "GameManager::hasActiveGame() called.";
    return m_hasActiveGame;
}


bool GameManager::isGameWon()
{
    qDebug() << "GameManager::isGameWon() called.";
    return m_isGameWon;
}

bool GameManager::isGameLost()
{
    qDebug() << "GameManager::isGameLost() called.";
    return m_isGameLost;
}

bool GameManager::loadWords()
{
    qDebug() << "GameManager::loadWords() called.";
    QFile file("Wordle/resources/words.txt");
    QString path = QDir::currentPath();
    qDebug() << "Some address." << path.toUtf8();
    if (!file.exists())
    {
        qDebug() << "GameManager::loadWords() called. File does not exist.";
        return false;
    }

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return false;
    }
    while (!file.atEnd())
    {
        QString line = file.readLine();
        line = line.trimmed();
        m_words.insert(line, line.length());
    }
    file.close();
    return true;
}

bool GameManager::checkIfWordExists(QString word)
{
    qDebug() << "GameManager::checkIfWordExists() called.";
    return m_words.contains(word);
}

QString GameManager::getRandomWord()
{
    qDebug() << "GameManager::getRandomWord() called.";
    QRandomGenerator *generator = QRandomGenerator::global();
    int randomIndex = generator->bounded(0, m_words.size());
    QString randomWord = m_words.keys().at(randomIndex);
    return randomWord;
}

QString GameManager::evaluateGuess(QString guess)
{
    /*
    For our game, each guess has 5 cell and these cells has colors.
    After the user presses enter, we need to evaluate the guess.
    Evaluation process returns a string with 5 characters.
    If Letter is in the secret word and in the correct position, the cell should be green, represented by G.
    If Letter is in the secret word but in the wrong position, the cell should be yellow, represented by Y.
    If Letter is not in the secret word, the cell should be grey, represented by X.
    For example, if the secret word is "HELLO" and the guess is "HELLO", the evaluation string should be "GGGGG".
    If the secret word is "HELLO" and the guess is "HOLLY", the evaluation string should be "GGYXX".
    */
    qDebug() << "GameManager::evaluateGuess() called.";
    // check if guess is secret word
    if (guess == m_secretWord)
    {
        qDebug() << "GameManager::evaluateGuess() called. Guess is secret word.";
        return "GGGGG";
    }

    QString evaluation = "";
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (guess[i] == m_secretWord[i])
        {
            evaluation += "G";
        }
        else if (m_secretWord.contains(guess[i]))
        {
            evaluation += "Y";
        }
        else
        {
            evaluation += "X";
        }
    }

    return evaluation;
}

void GameManager::updateKeyboard(QString evaluation, QString guess)
{
    qDebug() << "GameManager::updateKeyboard() called.";
    for (int i = 0; i < WORD_LENGTH; i++)
    {
        if (evaluation[i] == 'G')
        {
            qDebug() << "GameManager::updateKeyboard() called. Updating green letter." << guess[i];
            m_greens.append(guess[i]);
            emit keyColorUpdated(GREEN_COLOR, guess[i].toUpper());
        }
        else if (evaluation[i] == 'Y') // Prevent green letter to be yellow back.
        {   
            qDebug() << "GameManager::updateKeyboard() called. Updating yellow letter." << guess[i];
            // dont update if m_greens contains guess[i]
            if (!m_greens.contains(guess[i]))
            {
                emit keyColorUpdated(YELLOW_COLOR, guess[i].toUpper());
            }
        }
        else
        {
            qDebug() << "GameManager::updateKeyboard() called. Updating gray letter." << guess[i];
            emit keyColorUpdated(GRAY_COLOR, guess[i].toUpper());
        }
    }

    // display m_greens 
    qDebug() << "GameManager::updateKeyboard() called. m_greens contains: " << m_greens;
}