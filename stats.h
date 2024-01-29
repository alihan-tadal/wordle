#ifndef STATS_H
#define STATS_H

#include <QObject>

class Stats : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int gamePlays READ gamePlays NOTIFY gamePlaysChanged)
    Q_PROPERTY(int gameWins READ gameWins NOTIFY gameWinsChanged)
    Q_PROPERTY(int gameLosses READ gameLosses NOTIFY gameLossesChanged)
    Q_PROPERTY(int streak READ streak NOTIFY streakChanged)
    Q_PROPERTY(int maxStreak READ maxStreak NOTIFY maxStreakChanged)
    Q_PROPERTY(QChar lastResult READ lastResult NOTIFY lastResultChanged)
    Q_PROPERTY(QList<int> winDistribution READ winDistribution NOTIFY winDistributionChanged)

public:
    explicit Stats(QObject *parent = nullptr);

    void fromJson(const QJsonObject &json);

    // Getters
    int gamePlays() const;
    int gameWins() const;
    int gameLosses() const;
    int streak() const;
    int maxStreak() const;
    QChar lastResult() const;
    QList<int> winDistribution() const;

    // Setters
    void setGamePlays(int gamePlays);
    void setGameWins(int gameWins);
    void setGameLosses(int gameLosses);
    void setStreak(int streak);
    void setMaxStreak(int maxStreak);
    void setLastResult(QChar lastResult);
    void setWinDistribution(QList<int> winDistribution);

    void incrementGamePlays();
    void incrementWins();
    void incrementLosses();
    void incrementStreak();
    void makeItPermanent();
    void updateWinDistribution(int numGuesses);
    Q_INVOKABLE void resetStats();


signals:
    void aChanged();
    void gamePlaysChanged(int gamePlays);
    void gameWinsChanged(int gameWins);
    void gameLossesChanged(int gameLosses);
    void streakChanged(int streak);
    void lastResultChanged(QChar lastResult);
    void winDistributionChanged(QList<int> winDistribution);
    void maxStreakChanged(int maxStreak);

private:
    int m_gamePlays;
    int m_gameWins;
    int m_gameLosses;
    int m_streak;
    int m_maxStreak;
    QChar m_lastResult;
    QList<int> m_winDistribution;
};

#endif // STATS_H