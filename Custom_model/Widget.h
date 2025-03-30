#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ScoreInfoModel.h"
#include <QTableView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>

class Widget : public QWidget
{
    Q_OBJECT

    QVBoxLayout vlayout;
    QHBoxLayout hlayout;
    QTableView m_view;
    QMenu m_memu;
    ScoreInfoModel m_model;
    QPushButton refreshBtn;
    QPushButton clearBtn;
    QPushButton scoreBtn;

protected slots:
    void onRefreshBtnClicked();
    void onClearBtnClicked();
    void onScoreBtnClicked();
    void onDeleteActionClicked();

public:
    Widget(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent* event);
    ~Widget();
};
#endif // WIDGET_H
