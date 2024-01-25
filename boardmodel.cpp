#include <QAbstractTableModel>
#include <QColor>
#include <QDebug>
#include "boardmodel.h"
#include "cell.h"



BoardModel::BoardModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        QVector<Cell *> row;
        for (int j = 0; j < WORD_LENGTH; j++)
        {
            Cell *newCell = new Cell();
            newCell->setCellColor(QColor(Qt::white));
            newCell->setCellChar(' ');
            newCell->setIsLocked(false);
            newCell->setIsEmpty(true);
            row.append(newCell);
        }
        m_data.append(row);
    }
}

int BoardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.size();
}

int BoardModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data[0].size();
}

QVariant BoardModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    switch (role)
    {
    case CellColorRole:
        return m_data[index.row()][index.column()]->cellColor();
    case CellCharRole:
        return m_data[index.row()][index.column()]->cellChar();
    case IsLockedRole:
        return m_data[index.row()][index.column()]->isLocked();
    case IsEmptyRole:
        return m_data[index.row()][index.column()]->isEmpty();
    }

    return QVariant();
}

QHash<int, QByteArray> BoardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CellColorRole] = "cellColor";
    roles[CellCharRole] = "cellChar";
    roles[IsLockedRole] = "isLocked";
    roles[IsEmptyRole] = "isEmpty";
    return roles;
}

void BoardModel::resetBoard()
{
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        for (int j = 0; j < WORD_LENGTH; j++)
        {
            m_data[i][j]->setCellColor(QColor(Qt::white));
            m_data[i][j]->setCellChar(' ');
            m_data[i][j]->setIsLocked(false);
            m_data[i][j]->setIsEmpty(true);
            emit dataChanged(index(i, j), index(i, j));
        }
    }
}

void BoardModel::insertLetter(QString letter)
{
    // find first unlocked row
    int firstUnlockedRow = -1;
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        if (!m_data[i][0]->isLocked())
        {
            firstUnlockedRow = i;
            break;
        }
    }
    // fill in the first unlocked row
    if (firstUnlockedRow != -1)
    {
        for (int i = 0; i < WORD_LENGTH; i++)
        {
            if (m_data[firstUnlockedRow][i]->isEmpty())
            {
                m_data[firstUnlockedRow][i]->setCellChar(letter[0]);
                m_data[firstUnlockedRow][i]->setIsEmpty(false);
                emit dataChanged(index(firstUnlockedRow, i), index(firstUnlockedRow, i));
                break;
            }
        }
    }

}

void BoardModel::removeLetter()
{
    int firstUnlockedRow = -1;
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        if (!m_data[i][0]->isLocked())
        {
            firstUnlockedRow = i;
            break;
        }
    }
    if (firstUnlockedRow != -1)
    {
        for (int i = WORD_LENGTH - 1; i >= 0; i--)
        {
            if (!m_data[firstUnlockedRow][i]->isEmpty())
            {
                m_data[firstUnlockedRow][i]->setCellChar(' ');
                m_data[firstUnlockedRow][i]->setIsEmpty(true);
                emit dataChanged(index(firstUnlockedRow, i), index(firstUnlockedRow, i));
                break;
            }
        }
    }
}

QString BoardModel::getGuess()
{
   int firstUnlockedRow = -1;
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        if (!m_data[i][0]->isLocked())
        {
            firstUnlockedRow = i;
            break;
        }
    }
    QString guess = "";
    if (firstUnlockedRow != -1)
    {
        for (int i = 0; i < WORD_LENGTH; i++)
        {
            if (!m_data[firstUnlockedRow][i]->isEmpty())
            {
                guess += m_data[firstUnlockedRow][i]->cellChar();
            }
        }
    }
    return guess;
}

void BoardModel::lockGuess(QString evaluation)
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
    // get first unlocked row.
    int firstUnlockedRow = -1;
    for (int i = 0; i < GUESS_LENGTH; i++)
    {
        if (!m_data[i][0]->isLocked())
        {
            firstUnlockedRow = i;
            break;
        }
    }

    if (firstUnlockedRow != -1) {
        for (int i = 0; i < WORD_LENGTH; i++) {
            if (evaluation[i] == 'G') {
                m_data[firstUnlockedRow][i]->setCellColor(GREEN_COLOR);
            } else if (evaluation[i] == 'Y') {
                m_data[firstUnlockedRow][i]->setCellColor(YELLOW_COLOR);
            } else if (evaluation[i] == 'X') {
                m_data[firstUnlockedRow][i]->setCellColor(GRAY_COLOR);
            }
            m_data[firstUnlockedRow][i]->setIsLocked(true);
            emit dataChanged(index(firstUnlockedRow, i), index(firstUnlockedRow, i));
        }
    }

    if (evaluation == "GGGGG") {
        // fill remaining parts of the board with green
        for (int i = firstUnlockedRow + 1; i < GUESS_LENGTH; i++) {
            for (int j = 0; j < WORD_LENGTH; j++) {
                m_data[i][j]->setCellColor(GREEN_COLOR);
                m_data[i][j]->setIsLocked(true);
                // set cell to the answer letter
                m_data[i][j]->setCellChar(m_data[firstUnlockedRow][j]->cellChar());
                emit dataChanged(index(i, j), index(i, j));
            }
        }
    }

    if (firstUnlockedRow == GUESS_LENGTH - 1) {
        qDebug() << "BoardModel::lockGuess() called. Board is full.";
        emit boardIsFull();
    }
    
}