#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QtQml/qqml.h>

class GameManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(bool hasActiveGame READ hasActiveGame NOTIFY hasActiveGameChanged)

public:
    explicit GameManager(QObject *parent = nullptr);
    void setHasActiveGame(bool hasActiveGame);
    Q_INVOKABLE bool hasActiveGame();


public slots:
    void onStartGameRequested();
    void onExitGameRequested();

signals:
    void hasActiveGameChanged(bool hasActiveGame);

private:
    bool m_hasActiveGame;
};

#endif // GAMEMANAGER_H
