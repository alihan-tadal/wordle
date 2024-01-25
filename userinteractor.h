#ifndef USERINTERACTOR_H
#define USERINTERACTOR_H

#include <QObject>
#include <QKeyEvent>


/** Uses event filter to catch letter press, backspace and enter keys.**/
class UserInteractor : public QObject
{
    Q_OBJECT
public:
    explicit UserInteractor(QObject *parent = nullptr);
    ~UserInteractor();
    bool eventFilter(QObject *obj, QEvent *event);
    // Create emitSignal functions for qml to call
    Q_INVOKABLE void emitStartGame(); // For qml elements to call
    Q_INVOKABLE void emitExitGame(); // For qml elements to call

public slots:

signals:
    void letterPressed(QString letter);
    void backspacePressed();
    void enterPressed();

    void startGameRequested();
    void exitGameRequested();
};

#endif // USERINTERACTOR_H
