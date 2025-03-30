#include "ScoreInfoModel.h"

ScoreInfoModel::ScoreInfoModel(QObject *parent)
    : QObject{parent}
{}

bool ScoreInfoModel::add(const ScoreInfo& info){
    QStandardItem* root = m_model.invisibleRootItem();
    if(!root){
        return false;
    }

    if(m_model.rowCount() == 0){
        m_model.setHorizontalHeaderLabels({"ID", "Name", "Score"});
    }
    QList<QStandardItem*> items {
        new QStandardItem(),
        new QStandardItem(),
        new QStandardItem()
    };

    if(items[0] && items[1] && items[2]){
        items[0]->setData(info.id(), Qt::DisplayRole);
        items[1]->setData(info.name(), Qt::DisplayRole);
        items[2]->setData(info.score(), Qt::DisplayRole);

        root->appendRow(items);
        return true;
    }
    qDeleteAll(items);
    return false;
}

bool ScoreInfoModel::add(const QList<ScoreInfo>& list){
    if(list.isEmpty()){
        return true;
    }
    bool status = true;
    for(const ScoreInfo& info : list){
        status &= add(info);
    }
    return status;
}

bool ScoreInfoModel::remove(int i){
    if(i < 0 || i >= count()){
        return false;
    }
    m_model.removeRow(i);
    return true;
}

ScoreInfo ScoreInfoModel::getItem(int i) {
    if(i < 0 || i >= count()){
        return ScoreInfo();
    }
    QModelIndex parent;
    QModelIndex index0 = m_model.index(i, 0, parent);
    QModelIndex index1 = m_model.index(i, 1, parent);
    QModelIndex index2 = m_model.index(i, 2, parent);

    return ScoreInfo(
        index0.data().toString(),
        index1.data().toString(),
        index2.data().toInt()
        );
}

void ScoreInfoModel::clear(){
    m_model.clear();
}

int ScoreInfoModel::count(){
    return m_model.rowCount();
}

void ScoreInfoModel::setView(QTableView& view){
    view.setModel(&m_model);
}
