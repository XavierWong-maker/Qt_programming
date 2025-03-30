#ifndef DATASOURE_H
#define DATASOURE_H

#include "ScoreInfo.h"
#include <QObject>

class DataSoure : public QObject
{
    Q_OBJECT

    ScoreInfo info;
    QList<ScoreInfo> m_data;
    bool parse(const QString& line, ScoreInfo& info);
public:
    explicit DataSoure(QObject *parent = nullptr);
    bool setDataPath(const QString& path);
    QList<ScoreInfo> fetchData();
    int count();
};

#endif // DATASOURE_H
