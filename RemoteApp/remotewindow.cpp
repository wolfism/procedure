#include "remotewindow.h"

RemoteWindow::RemoteWindow()
{
    seekHelpPage    = Q_NULLPTR;
    goHelpPage      = Q_NULLPTR;
    head            = Q_NULLPTR;

    seekHelpPageTwo  = Q_NULLPTR;
    seekHelpPageThree= Q_NULLPTR;

    goHelpPageTwo   = Q_NULLPTR;
    goHelpPageThree = Q_NULLPTR;
    goHelpPagefour  = Q_NULLPTR;

    tit= this->titlebar();

    initUI();
    onnections();
}

void RemoteWindow::initUI()
{
    QImage *ima=new QImage;
    ima->load(":/images/theme.svg");
    DLabel* pic=new DLabel(this);
    pic->setPixmap(QPixmap::fromImage(*ima));
    pic->setScaledContents(true);
    pic->setFixedSize(60,60);

    DLabel* tips=new DLabel(this);
    tips->setText("这是由Deepin团队开发的远程协助应用，\n"
                  "如果您在使用过程中遇到了困难，或者有人求助于你，\n"
                  "请点击下方的我要求助或帮助别人");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips->setPalette(pe);

    seekButton=new DToolButton(this);
    seekButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    seekButton->setIcon(QIcon(QPixmap(":/images/seekHelp.svg")));
    seekButton->setText("我要求助");
    seekButton->setFixedSize(180,35);
    ft.setPointSize(12);
    seekButton->setFont(ft);

    goButton=new DToolButton(this);
    goButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    goButton->setIcon(QIcon(QPixmap(":/images/toHelp.svg")));
    goButton->setText("帮助别人");
    goButton->setFixedSize(180,35);
    goButton->setFont(ft);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(10);
    layout->addWidget(pic,0,Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(10);
    layout->addWidget(seekButton,0,Qt::AlignHCenter);
    layout->addSpacing(5);
    layout->addWidget(goButton,0,Qt::AlignHCenter);
    layout->addSpacing(20);

    headPage=new DWidget(this);
    headPage->setLayout(layout);

    pageStacked=new DStackedWidget(this);
    pageStacked->addWidget(headPage);

    setCentralWidget(pageStacked);
    setFixedSize(360,320);
    left = nullptr;
}

void RemoteWindow::onnections()
{
    connect(seekButton,&DToolButton::clicked,this,&RemoteWindow::on_seekHelpPage_push);
    connect(goButton,&DToolButton::clicked,this,&RemoteWindow::on_goHelp_push);
}

void RemoteWindow::setAppTitle(const QString &path,const QString &name)
{
    if(!head)
    {
        QImage *ima=new QImage;
        left=new DLabel(this);
        left->setPixmap(QPixmap::fromImage(*ima));
        left->setScaledContents(true);
        left->setFixedSize(16,16);
        right=new DLabel(this);

        QHBoxLayout* myLayout = new QHBoxLayout();
        myLayout->addSpacing(150);
        myLayout->addWidget(left);
        myLayout->addSpacing(1);
        myLayout->addWidget(right);


        head = new DWidget(this);
        head->setLayout(myLayout);
        tit->setCustomWidget(head);
    }
    left->setPixmap(QPixmap(path));
    right->setText(name);
}

void RemoteWindow::seekHelp_pageOne()
{
    DSpinner * waitIco=new DSpinner(this);
    waitIco->setFixedSize(32,32);
    waitIco->start();

    DLabel* tips=new DLabel(this);
    tips->setText("正在生成请求验证码，请稍后...");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(12);
    tips->setFont(ft);

    DSuggestButton *cancelButton = new DSuggestButton(this);
    cancelButton->setText("取消");
    cancelButton->setFixedSize(180,35);
    ft.setPointSize(12);
    cancelButton->setFont(ft);

    connect(cancelButton,&DSuggestButton::clicked,
    [=](){
        //恢复title
        setAppTitle(nullptr,"远程协助");
        pageStacked->setCurrentWidget(headPage);
        timer1->stop();
    });

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addSpacing(50);
    layout->addWidget(waitIco,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(cancelButton,0,Qt::AlignHCenter);
    layout->addSpacing(20);

    seekHelpPageOne=new DWidget(this);
    seekHelpPageOne->setLayout(layout);
    seekHelpPage->addWidget(seekHelpPageOne);
}

void RemoteWindow::seekHelp_pageTwo()
{
    authCode=new DLabel(this);
    QFont ft1;
    ft1.setPointSize(24);
    ft1.setLetterSpacing(QFont::AbsoluteSpacing,18);
    authCode->setFont(ft1);

    DLabel* tips=new DLabel(this);
    tips->setText("要开始共享您的桌面，请讲上面的验证码提供给协助您的人员\n"
                  "他们输入验证码后，您的共享会话会立即开始");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips->setPalette(pe);

    DSuggestButton *cpButton = new DSuggestButton(this);
    cpButton->setText("复制");
    cpButton->setFixedSize(180,35);
    ft.setPointSize(12);
    cpButton->setFont(ft);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(authCode,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(cpButton,0,Qt::AlignHCenter);
    layout->addSpacing(30);

    seekHelpPageTwo=new DWidget(this);
    seekHelpPageTwo->setLayout(layout);
    seekHelpPage->addWidget(seekHelpPageTwo);

    connect(cpButton,&DSuggestButton::clicked,[=](){
        QClipboard *board = QApplication::clipboard();
        board->setText(authCode->text());
        waitingToConnect();
    });
}

void RemoteWindow::seekHelp_pageThree()
{
    DLabel* tips=new DLabel(this);
    tips->setText("成功复制到剪切板");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(18);
    tips->setFont(ft);

    DLabel* tips2=new DLabel(this);
    tips2->setText("正在等待连接，请稍后...\n"
                  "连接成功后，此页面会自动隐藏到任务栏");
    tips2->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips2->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips2->setPalette(pe);

    DSuggestButton *backButton = new DSuggestButton(this);
    backButton->setText("返回主界面");
    backButton->setFixedSize(180,35);
    ft.setPointSize(12);
    backButton->setFont(ft);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips2,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(backButton,0,Qt::AlignHCenter);
    layout->addSpacing(30);

    seekHelpPageThree=new DWidget(this);
    seekHelpPageThree->setLayout(layout);
    seekHelpPage->addWidget(seekHelpPageThree);

    connect(backButton,&DSuggestButton::clicked,[=](){
        setAppTitle(nullptr,"远程协助");
        pageStacked->setCurrentWidget(headPage);
    });
}

void RemoteWindow::goHelp_pageOne()
{

    input= new QLineEdit(this);
    input->setAlignment( Qt::AlignHCenter);;
    QRegExp rx("[0-9]{6}");
    input->setValidator(new QRegExpValidator(rx, this));
    input->setFixedSize(330,70);
    QFont ft1;
    ft1.setPointSize(24);
    ft1.setLetterSpacing(QFont::AbsoluteSpacing,18);
    input->setFont(ft1);

    DLabel* tips=new DLabel(this);
    tips->setText("请在上方输入您想帮助人提供给你的验证码，\n"
                  "完成后点击连接开始协助对方");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips->setPalette(pe);

    cancelButton = new DSuggestButton(this);
    cancelButton->setText("取消");
    cancelButton->setFixedSize(180,35);
    ft.setPointSize(12);
    cancelButton->setFont(ft);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addSpacing(50);
    layout->addWidget(input,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(cancelButton,0,Qt::AlignHCenter);
    layout->addSpacing(20);

    goHelpPageOne=new DWidget(this);
    goHelpPageOne->setLayout(layout);
    goHelpPage->addWidget(goHelpPageOne);

    connect(input,&QLineEdit::textChanged,[=](const QString &text){
        if(text.size()==6){
            inputCode=text;
            cancelButton->setText("连接");
        }
        else {
            cancelButton->setText("取消");
        }
    });
    connect(cancelButton,&DSuggestButton::clicked,[=](){
        if(cancelButton->text()=="取消"){
            cancelButton->setText("取消");
            pageStacked->setCurrentWidget(headPage);
            setAppTitle(nullptr,"远程协助");
        }
        else {
            goConnect();
        }
    });
}

void RemoteWindow::goHelp_pageTwo()
{
    DSpinner * waitIco=new DSpinner(this);
    waitIco->setFixedSize(32,32);
    waitIco->start();

    DLabel* tips=new DLabel(this);
    tips->setText("正在建立连接，请稍后...");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(12);
    tips->setFont(ft);

    DSuggestButton *cancelButton = new DSuggestButton(this);
    cancelButton->setText("取消");
    cancelButton->setFixedSize(180,35);
    ft.setPointSize(12);
    cancelButton->setFont(ft);

    connect(cancelButton,&DSuggestButton::clicked,
    [=](){
        //恢复title
        timer2->stop();
        setAppTitle(nullptr,"远程协助");
        pageStacked->setCurrentWidget(headPage);
    });

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addSpacing(50);
    layout->addWidget(waitIco,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(cancelButton,0,Qt::AlignHCenter);
    layout->addSpacing(20);

    goHelpPageTwo=new DWidget(this);
    goHelpPageTwo->setLayout(layout);
    goHelpPage->addWidget(goHelpPageTwo);
}

void RemoteWindow::goHelp_pageThree()
{
    DLabel* tips=new DLabel(this);
    tips->setText("连接失败");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(18);
    tips->setFont(ft);
    DPalette pe1;
    pe1.setColor(DPalette::WindowText, Qt::darkYellow);
    tips->setPalette(pe1);

    DLabel* tips2=new DLabel(this);
    tips2->setText("网络连接状态不是很稳定\n"
                  "点击重试按钮再次尝试连接");
    tips2->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips2->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips2->setPalette(pe);

    DSuggestButton *retryButton = new DSuggestButton(this);
    retryButton->setText("重试");
    retryButton->setFixedSize(180,35);
    ft.setPointSize(12);
    retryButton->setFont(ft);

    connect(retryButton,&DSuggestButton::clicked,[=](){
        goHelpPage->setCurrentWidget(goHelpPageOne);
        input->clear();
//        cancelButton->setText("取消");
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips2,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(retryButton,0,Qt::AlignHCenter);
    layout->addSpacing(30);

    goHelpPageThree=new DWidget(this);
    goHelpPageThree->setLayout(layout);
    goHelpPage->addWidget(goHelpPageThree);
}

void RemoteWindow::goHelp_pagefour()
{
    DLabel* tips=new DLabel(this);
    tips->setText("您正在进行远程协助");
    tips->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(18);
    tips->setFont(ft);

    DLabel* tips2=new DLabel(this);
    tips2->setText("当前已经由一个连接会话，\n"
                  "如果想建立新的连接，请先断开");
    tips2->setAlignment(Qt::AlignHCenter);
    ft.setPointSize(8);
    tips2->setFont(ft);
    DPalette pe;
    pe.setColor(DPalette::WindowText, Qt::gray);
    tips2->setPalette(pe);

    DSuggestButton *breakButton = new DSuggestButton(this);
    breakButton->setText("断开");
    breakButton->setFixedSize(180,35);
    ft.setPointSize(12);
    breakButton->setFont(ft);

    connect(breakButton,&DSuggestButton::clicked,
    [=](){
        //恢复title
        setAppTitle(nullptr,"远程协助");
        pageStacked->setCurrentWidget(headPage);
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addSpacing(50);
    layout->addWidget(tips,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(tips2,0,Qt::AlignHCenter);
    layout->addSpacing(30);
    layout->addWidget(breakButton,0,Qt::AlignHCenter);
    layout->addSpacing(30);

    goHelpPagefour=new DWidget(this);
    goHelpPagefour->setLayout(layout);
    goHelpPage->addWidget(goHelpPagefour);
}

void RemoteWindow::on_seekHelpPage_push()
{
    //切换title
    setAppTitle(":/images/seekHelp.svg","我要求助");

    if(!seekHelpPage)
    {
        seekHelpPage = new DStackedWidget(this);
        pageStacked->addWidget(seekHelpPage);
        seekHelp_pageOne();
        //定时器1
        timer1 = new QTimer(this);
        connect(timer1,SIGNAL(timeout()),this,SLOT(timerDone()));
    }
    pageStacked->setCurrentWidget(seekHelpPage);
    seekHelpPage->setCurrentWidget(seekHelpPageOne);
    timer1->start(2000);
}

void RemoteWindow::on_goHelp_push()
{
    setAppTitle(":/images/toHelp.svg","帮助别人");
    if(!goHelpPage)
    {
        goHelpPage=new DStackedWidget(this);
        pageStacked->addWidget(goHelpPage);
        goHelp_pageOne();
    }
    input->clear();
    pageStacked->setCurrentWidget(goHelpPage);
    goHelpPage->setCurrentWidget(goHelpPageOne);
}

void RemoteWindow::timerDone()
{
    if(!seekHelpPageTwo){
        seekHelp_pageTwo();
    }
    timer1->stop();
    getCode=QString::number(QRandomGenerator::global()->bounded(900000)+100000);
    authCode->setText(getCode);
    seekHelpPage->setCurrentWidget(seekHelpPageTwo);
}

void RemoteWindow::waitingToConnect()
{
    if(!seekHelpPageThree){
        seekHelp_pageThree();
    }
    seekHelpPage->setCurrentWidget(seekHelpPageThree);
}


void RemoteWindow::goConnect()
{
    if(!goHelpPageTwo){
        goHelp_pageTwo();
        //定时器2
        timer2 = new QTimer(this);
        connect(timer2,&QTimer::timeout,[this](){
            timer2->stop();
            if(getCode!=inputCode){
                connectFail();
            }
            else {
                connectSucess();
            }
        });
    }
    goHelpPage->setCurrentWidget(goHelpPageTwo);
    timer2->start(5000);
}

void RemoteWindow::connectFail()
{
    if(!goHelpPageThree){
        goHelp_pageThree();
    }
    goHelpPage->setCurrentWidget(goHelpPageThree);
}

void RemoteWindow::connectSucess()
{
    if(!goHelpPagefour){
        goHelp_pagefour();
    }
    goHelpPage->setCurrentWidget(goHelpPagefour);
}
