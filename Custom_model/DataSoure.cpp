#include "DataSoure.h"
#include <QFile>
#include <QTextStream>

DataSoure::DataSoure(QObject *parent)
    : QObject{parent}
{}

bool DataSoure::setDataPath(const QString& path){

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return false;
    }
    {
        QTextStream in(&file);
        while(!in.atEnd()){
            ScoreInfo info;
            QString line = in.readLine();
            if(!line.isEmpty() && parse(line, info)){
                m_data.append(info);
            }
        }
    }
    return true;
}

bool DataSoure::parse(const QString& line, ScoreInfo& info){
    QStringList list = line.split(",", Qt::SkipEmptyParts);
    if(list.count() != 3){
        return false;
    }
    const QString id = list[0].trimmed();
    const QString name = list[1].trimmed();
    const QString scoreStr = list[2].trimmed();

    bool conversionOK = false;
    const int score = scoreStr.toInt(&conversionOK);

    if(!conversionOK || score < 0 || score > 150){
        return false;
    }

    info = ScoreInfo(id, name, score);
    return true;
}

QList<ScoreInfo> DataSoure::fetchData(){
    QList<ScoreInfo> result;
    result.swap(m_data);
    return result;
}

int DataSoure::count(){
    return m_data.count();
}
