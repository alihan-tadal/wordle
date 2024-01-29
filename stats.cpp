#include "stats.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Stats::Stats(QObject *parent)
    : QObject{parent}
{
    // read json file to get stats
    QFile file("Wordle/resources/stats.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = file.readAll();
    // convert to json document
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    fromJson(obj);
    file.close();
    qDebug() << "Stats::Stats() called.";
}


void Stats::fromJson(const QJsonObject &json)
{
    // parse json object and set values
    setGamePlays(json["gamePlays"].toInt());
    setGameWins(json["gameWins"].toInt());
    setGameLosses(json["gameLosses"].toInt());
    setStreak(json["streak"].toInt());
    setMaxStreak(json["maxStreak"].toInt());
    setLastResult(json["lastResult"].toString().at(0));
    QJsonArray jsonArray = json["winDistribution"].toArray();
    for (int i = 0; i < jsonArray.size(); i++)
    {
        m_winDistribution.append(jsonArray[i].toInt());
    }
}

// Getters //
int Stats::gamePlays() const
{
    return m_gamePlays;
}

int Stats::gameWins() const
{
    return m_gameWins;
}

int Stats::gameLosses() const
{
    return m_gameLosses;
}

int Stats::streak() const
{
    return m_streak;
}

int Stats::maxStreak() const
{
    return m_maxStreak;
}

QChar Stats::lastResult() const
{
    return m_lastResult;
}

QList<int> Stats::winDistribution() const
{
    return m_winDistribution;
}


// Setters // 
void Stats::setGamePlays(int gamePlays)
{
    if (m_gamePlays == gamePlays)
        return;

    m_gamePlays = gamePlays;
    emit gamePlaysChanged(m_gamePlays);
}

void Stats::setGameWins(int gameWins)
{
    if (m_gameWins == gameWins)
        return;

    m_gameWins = gameWins;
    emit gameWinsChanged(m_gameWins);
}

void Stats::setGameLosses(int gameLosses)
{
    if (m_gameLosses == gameLosses)
        return;

    m_gameLosses = gameLosses;
    emit gameLossesChanged(m_gameLosses);
}

void Stats::setStreak(int streak)
{
    if (m_streak == streak)
        return;

    m_streak = streak;
    emit streakChanged(m_streak);
}

void Stats::setMaxStreak(int maxStreak)
{
    if (m_maxStreak == maxStreak)
        return;

    m_maxStreak = maxStreak;
    emit maxStreakChanged(m_maxStreak);
}

void Stats::setLastResult(QChar lastResult)
{
    if (m_lastResult == lastResult)
        return;

    m_lastResult = lastResult;
    emit lastResultChanged(m_lastResult);
}

void Stats::setWinDistribution(QList<int> winDistribution)
{
    if (m_winDistribution == winDistribution)
        return;

    m_winDistribution = winDistribution;
    emit winDistributionChanged(m_winDistribution);
}

void Stats::incrementGamePlays()
{
    m_gamePlays++;
    emit gamePlaysChanged(m_gamePlays);
}

void Stats::incrementWins()
{
    m_gameWins++;
    emit gameWinsChanged(m_gameWins);
}

void Stats::incrementLosses()
{
    m_gameLosses++;
    emit gameLossesChanged(m_gameLosses);
}

void Stats::incrementStreak()
{
    m_streak++;
    emit streakChanged(m_streak);
}

void Stats::makeItPermanent() {
    // read json file to get stats
    QFile file("Wordle/resources/stats.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray data = file.readAll();
    // convert to json document
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();
    obj["gamePlays"] = m_gamePlays;
    obj["gameWins"] = m_gameWins;
    obj["gameLosses"] = m_gameLosses;
    obj["streak"] = m_streak;
    obj["maxStreak"] = m_maxStreak;
    obj["lastResult"] = QString(m_lastResult);
    QJsonArray jsonArray;
    for (int i = 0; i < m_winDistribution.size(); i++)
    {
        jsonArray.append(m_winDistribution[i]);
    }
    obj["winDistribution"] = jsonArray;
    file.close();
    // write to file
    QFile file2("Wordle/resources/stats.json");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonDocument doc2(obj);
    file2.write(doc2.toJson());
    file2.close();
    qDebug() << "Stats::makeItPermanent() called.";
}

void Stats::resetStats()
{
    m_gamePlays = 0;
    m_gameWins = 0;
    m_gameLosses = 0;
    m_streak = 0;
    m_maxStreak = 0;
    m_lastResult = 'L';
    m_winDistribution.clear();
    for (int i = 0; i < 6; i++)
    {
        m_winDistribution.append(0);
    }
    makeItPermanent();
    emit gamePlaysChanged(m_gamePlays);
    emit gameWinsChanged(m_gameWins);
    emit gameLossesChanged(m_gameLosses);
    emit streakChanged(m_streak);
    emit maxStreakChanged(m_maxStreak);
    emit lastResultChanged(m_lastResult);
    emit winDistributionChanged(m_winDistribution);
    qDebug() << "Stats::resetStats() called.";
}

void Stats::updateWinDistribution(int numGuesses)
{
    m_winDistribution[numGuesses-1]++;
    emit winDistributionChanged(m_winDistribution);
    qDebug() << "Stats::updateWinDistribution() called.";
}