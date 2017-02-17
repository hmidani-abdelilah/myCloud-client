#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QMenu>

#include "login.h"
#include "panel.h"
#include "userrequest.h"
#include "qlabelcustom.h"
#include "subscribepopup.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    QLabelCustom    *_pageName;

    QLabelCustom    *_labelCustom;
    QLabelCustom    *_labelLastName;
    QLabelCustom    *_labelFirstName;
    QLabelCustom    *_labelFreeSize;
    QLabelCustom    *_btnParamsAccount;
    Panel           *_mainPanel;
    QMenu            _menu;
    Login           *_loginView;
    UserRequest     *_userRequest;

public slots:
    void activeMainView(QNetworkReply *reply);

private slots:
    void stackerWidgetChanged(int index);
    void slotChangePageName(QString name);
    void menuParamsRequested(const QPoint &pos);
    void actionDisconnection(bool);
    void slotDisconnected(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
