#ifndef SCOREINFO_H
#define SCOREINFO_H

#include <QObject>
#include <QString>

class ScoreInfo : public QObject
{
    Q_OBJECT

    QString m_id;
    QString m_name;
    int m_score;

public:
    explicit ScoreInfo(QObject *parent = nullptr);
    ScoreInfo(QString id, QString name, int score, QObject *parent = nullptr);
    ScoreInfo(const ScoreInfo& obj);
    ScoreInfo& operator= (const ScoreInfo& obj);
    QString id() const;
    QString name() const;
    int score() const;

};

#endif // SCOREINFO_H
