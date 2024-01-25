#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QAbstractTableModel>
#include <QtQml/qqml.h>
#include "cell.h"

#define WORD_LENGTH 5
#define GUESS_LENGTH 6

#define GREEN_COLOR QColor("#6aaa64")
#define YELLOW_COLOR QColor("#c9b458")
#define GRAY_COLOR QColor("#787c7e")

class BoardModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BoardModel(QObject *parent = nullptr);
    enum BoardModelRoles {
        CellColorRole = Qt::UserRole + 1,
        CellCharRole,
        IsLockedRole,
        IsEmptyRole
    };

    int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    void resetBoard();

    void insertLetter(QString letter);

    void removeLetter();
    QString getGuess();
    void lockGuess(QString evaluation);
    
signals:
    void boardIsFull();
    
private:
    QVector<QVector<Cell *>> m_data;
};

#endif // BOARD_H
