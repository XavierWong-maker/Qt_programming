#include "Widget.h"
#include "DataSoure.h"
#include "ScoreInfo.h"
#include <QEvent>
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent): QWidget(parent), m_view(this){

    refreshBtn.setText("Refresh");
    clearBtn.setText("Clear");
    scoreBtn.setText("Score");

    hlayout.addWidget(&refreshBtn);
    hlayout.addWidget(&clearBtn);
    hlayout.addWidget(&scoreBtn);

    vlayout.addWidget(&m_view);
    vlayout.addLayout(&hlayout);
    setLayout(&vlayout);

    m_memu.addAction("Delete");

    m_model.setView(m_view);
    m_view.installEventFilter(this);

    connect(&refreshBtn, &QPushButton::clicked, this, &Widget::onRefreshBtnClicked);
    connect(&clearBtn, &QPushButton::clicked, this, &Widget::onClearBtnClicked);
    connect(&scoreBtn, &QPushButton::clicked, this, &Widget::onScoreBtnClicked);

    connect(m_memu.actions().first(), &QAction::triggered, this, &Widget::onDeleteActionClicked);

    onRefreshBtnClicked();
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

void Widget::onClearBtnClicked(){
    m_model.clear();
}

void Widget::onScoreBtnClicked(){
    const int count = m_model.count();
    if(0 == count){
        QMessageBox::information(this, "Statisti", "No data record!", QMessageBox::Ok);
        return;
    }

    int min = std::numeric_limits<int>::max();
    int max = std::numeric_limits<int>::min();
    qint64 sum {0};

    for(int i = 0; i < count; ++i){
        const int score = m_model.getItem(i).score();
        min = std::min(min, score);
        max = std::max(max, score);
        sum += score;
    }

    const int average = static_cast<int>(sum / count);

    QMessageBox::information(this, "Statistic", QString(" Min: %1\n Max: %2\n Average: %3")
                                                    .arg(min).arg(max).arg(average), QMessageBox::Ok) ;
}

void Widget::onDeleteActionClicked(){
    m_model.remove(m_view.currentIndex().row());
    qDebug() << m_view.currentIndex().row();
}

bool Widget::eventFilter(QObject *watched, QEvent* event){
    if((watched == &m_view) && (event->type() == QEvent::ContextMenu)){
        m_memu.exec(cursor().pos());
        return true;
    }else{
        return QWidget::eventFilter(watched, event);
    }
}

Widget::~Widget() {}
