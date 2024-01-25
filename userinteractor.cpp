
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include "userinteractor.h"

UserInteractor::UserInteractor(QObject *parent)
    : QObject{parent}
{}

UserInteractor::~UserInteractor()
{}

bool UserInteractor::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        auto keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Backspace) {
            qDebug() << "UserInteractor::eventFilter() called. Backspace pressed.";
            emit backspacePressed();
        } else if (keyEvent->key() == Qt::Key_Return) {
            qDebug() << "UserInteractor::eventFilter() called. Enter pressed.";
            emit enterPressed();
        } else if (keyEvent->key() >= Qt::Key_A && keyEvent->key() <= Qt::Key_Z) {
            qDebug() << "UserInteractor::eventFilter() called. Key pressed: " << keyEvent->text();
            emit letterPressed(keyEvent->text());
        }
    }
    return QObject::eventFilter(obj, event);
}


void UserInteractor::emitStartGame()
{
    qDebug() << "UserInteractor::emitStartGame() called.";
    emit startGameRequested();
    qDebug() << "UserInteractor::startGameRequested() emitted.";
}

void UserInteractor::emitExitGame()
{
    qDebug() << "UserInteractor::emitExitGame() called.";
    emit exitGameRequested();
    qDebug() << "UserInteractor::exitGameRequested() emitted.";
}
