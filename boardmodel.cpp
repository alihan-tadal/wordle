#include <QAbstractTableModel>
#include <QColor>
#include "boardmodel.h"
#include "cell.h"


#define WORD_LENGTH 5
#define GUESS_LENGTH 6

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