#include "Widget.h"
#include "DataSoure.h"
#include "ScoreInfo.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent){


}

void Widget::onRefreshBtnClicked(){
    m_model.clear();
    static const QString dataPath = "D:/Github/Qt_programming/NotePad/test.txt";
    DataSoure ds;
    if(!ds.setDataPath(dataPath)){
        QMessageBox::critical(this, "Error", "Read data Error!", QMessageBox::Ok);
        return;
    }
    m_model.add(ds.fetchData());
}

Widget::~Widget() {}
