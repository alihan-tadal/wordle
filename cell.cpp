#include <QColor>
#include <QChar>
#include "cell.h"

Cell::Cell(QObject *parent)
    : QObject{parent}
{}

QColor Cell::cellColor() const
{
    return m_cellColor;
}

void Cell::setCellColor(const QColor &newCellColor)
{
    m_cellColor = newCellColor;
}

QChar Cell::cellChar() const
{
    return m_cellChar;
}

void Cell::setCellChar(const QChar &newCellChar)
{
    m_cellChar = newCellChar;
}

bool Cell::isLocked() const
{
    return m_isLocked;
}

void Cell::setIsLocked(const bool newIsLocked)
{
    m_isLocked = newIsLocked;
}

bool Cell::isEmpty() const
{
    return m_isEmpty;
}

void Cell::setIsEmpty(const bool newIsEmpty)
{
    m_isEmpty = newIsEmpty;
}
