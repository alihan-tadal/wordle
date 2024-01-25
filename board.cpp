#include <QAbstractTableModel>
#include "board.h"
#include "cell.h"

#define CELL_DIM_PX 64
#define CELL_SPACING_PX 12
#define BOARD_ROW_COUNT 6
#define BOARD_COLUMN_COUNT 5

Board::Board(QObject *parent)
    : QAbstractTableModel{parent}
{
   // create a board for 6 row 5 column
    for (int row = 0; row < BOARD_ROW_COUNT; ++row) {
        QVector<Cell *> cellVector;
        for (int column = 0; column < BOARD_COLUMN_COUNT; ++column) {
            Cell *cell = new Cell();
            cell->setCellChar(QChar('A' + row * 5 + column));
            cell->setCellColor(QColor(Qt::white));
            // set cell locked if row < 3
            if (row < 1) {
                cell->setIsLocked(true);
                cell->setCellChar(QChar('A'));
                cell->setCellColor(QColor("#6aaa64"));
            } else {
                cell->setIsLocked(false);
            }

            // set cell empty if row > 2
            // if (row > 2 && column < 3) {
            //     cell->setIsEmpty(false);
            // } else {
            //     cell->setIsEmpty(true);
            //     cell->setCellChar(QChar(' '));
            // }

            cellVector.append(cell);
        }
        m_board.append(cellVector);
    }
}

int Board::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_board.size();
}

int Board::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_board.at(0).size();
}

QVariant Board::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_board.size() || index.row() < 0)
        return QVariant();

    if (index.column() >= m_board.at(0).size() || index.column() < 0)
        return QVariant();

    if (role == CellColorRole)
        return m_board[index.row()][index.column()]->cellColor();

    if (role == CellCharRole)
        return m_board[index.row()][index.column()]->cellChar();

    if (role == IsLockedRole)
        return m_board[index.row()][index.column()]->isLocked();

    if (role == IsEmptyRole)
        return m_board[index.row()][index.column()]->isEmpty();

    return QVariant();
}

QHash<int, QByteArray> Board::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CellColorRole] = "cellColor";
    roles[CellCharRole] = "cellChar";
    roles[IsLockedRole] = "isLocked";
    roles[IsEmptyRole] = "isEmpty";
    return roles;
}

QString Board::text() const
{
    QString text;
    text.append("Board:\n");
    return text;
}


// HACKY, CHANGE LATER
int Board::boardWidthInPx() const
{
    // calculate total width for row count where each cell is 50px wide and 12px spacing between cells
    return m_board.at(0).size() * CELL_DIM_PX + CELL_SPACING_PX * (m_board.at(0).size() - 1);
}

int Board::boardHeightInPx() const
{
    // calculate total height for column count where each cell is 50px high and 12px spacing between cells
    return m_board.size() * CELL_DIM_PX + CELL_SPACING_PX * (m_board.size() - 1);
}