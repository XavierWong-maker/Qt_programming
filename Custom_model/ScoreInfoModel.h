#ifndef SCOREINFOMODEL_H
#define SCOREINFOMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QTableView>
#include "ScoreInfo.h"

class ScoreInfoModel : public QObject
{
    Q_OBJECT
    QStandardItemModel m_model;
public:
    explicit ScoreInfoModel(QObject *parent = nullptr);
    bool add(const ScoreInfo& info);
    bool add(const QList<ScoreInfo>& list);
    bool remove(int i);
    ScoreInfo getItem(int i);
    void clear();
    int count();
    void setView(QTableView& view);
};

#endif // SCOREINFOMODEL_H
