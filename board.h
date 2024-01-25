#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QAbstractTableModel>
#include "cell.h"
#include <QtQml/qqml.h>
class Board : public QAbstractTableModel
{
    Q_OBJECT
    // QML_ELEMENT
public:
    explicit Board(QObject *parent = nullptr);
    enum BoardRoles {
        CellColorRole = Qt::UserRole + 1,
        CellCharRole,
        IsLockedRole,
        IsEmptyRole
    };
signals:

    // QAbstractItemModel interface
public:
    Q_INVOKABLE int boardWidthInPx() const;
    Q_INVOKABLE int boardHeightInPx() const;
    int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    QString text() const;
private:
    QVector<QVector<Cell *>> m_board;
};

#endif // BOARD_H
