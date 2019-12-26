#ifndef REMOTEWINDOW_H
#define REMOTEWINDOW_H

#include <DApplication>
#include <DMainWindow>
#include <DToolButton>
#include <DStackedWidget>
#include <DLabel>
#include <DWidget>
#include <DPushButton>
#include <DTitlebar>
#include <DSpinner>
#include <DSuggestButton>

DWIDGET_USE_NAMESPACE

#include <QVBoxLayout>
#include <QString>
#include <QClipboard>
#include <QPixmap>
#include <QImage>
#include <QIcon>
#include <QTimer>
#include <QRandomGenerator>
#include <QLineEdit>
#include <QFont>
#include <QDebug>

class RemoteWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit RemoteWindow();
private:
    // 构建主窗口界面内容
    void initUI();
    // 初始化信号槽连接
    void onnections();

    void setAppTitle(const QString &path,const QString &name);

    void seekHelp_pageOne();
    void seekHelp_pageTwo();
    void seekHelp_pageThree();

    void goHelp_pageOne();
    void goHelp_pageTwo();
    void goHelp_pageThree();
    void goHelp_pagefour();

private slots:
    void on_seekHelpPage_push();
    void on_goHelp_push();

    void timerDone();
    void waitingToConnect();

    void goConnect();
    void connectFail();
    void connectSucess();
private:
    QString getCode;
    QString inputCode;
    QFont ft;

    QTimer *timer1;
    QTimer *timer2;

    DToolButton* seekButton;
    DToolButton* goButton;

    DTitlebar *tit;
    DWidget *head;
    DLabel * left;
    DLabel * right;

    DStackedWidget* pageStacked;
    DWidget *headPage;
    DLabel* authCode;

    DStackedWidget* seekHelpPage;
    DWidget *seekHelpPageOne;
    DWidget *seekHelpPageTwo;
    DWidget *seekHelpPageThree;

    DStackedWidget* goHelpPage;
    DWidget *goHelpPageOne;
    DSuggestButton *cancelButton;
    DWidget *goHelpPageTwo;
    DWidget *goHelpPageThree;
    DWidget *goHelpPagefour;
    QLineEdit * input;
};

#endif // REMOTEWINDOW_H
