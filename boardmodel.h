#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QAbstractTableModel>
#include <QtQml/qqml.h>
#include "cell.h"

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

signals:
private:
    QVector<QVector<Cell *>> m_data;
};

#endif // BOARD_H
