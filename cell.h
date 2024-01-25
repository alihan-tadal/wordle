#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QColor>

class Cell : public QObject
{
    Q_OBJECT
public:
    explicit Cell(QObject *parent = nullptr);
    QColor cellColor() const;
    void setCellColor(const QColor &newCellColor);

    QChar cellChar() const;
    void setCellChar(const QChar &newCellChar);

    bool isLocked() const;
    void setIsLocked(const bool newIsLocked);

    bool isEmpty() const;
    void setIsEmpty(const bool newIsEmpty);

signals:
    
private:
    QColor m_cellColor = QColor(Qt::white);
    QChar m_cellChar;
    bool m_isLocked = false;
    bool m_isEmpty = true;
};

#endif // CELL_H


