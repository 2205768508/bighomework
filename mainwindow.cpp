#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    button_gamestart = new QPushButton(this);
    button_gameoff = new QPushButton(this);

    button_gamestart->setGeometry(QRect(350,300,100,100));
    button_gamestart->setFlat(true);

    button_gamestart->setIcon(QIcon(QPixmap(":/image/start.png")));
    button_gamestart->setIconSize(QSize(100,100));

    button_gameoff->setGeometry(QRect(330,460,200,100));
    button_gameoff->setFlat(true);

    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(200,100));

    connect(button_gamestart,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gamestart_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/startInterface.png");
    QPixmap wechat(":/image/wechat.png");
    QPixmap QQ(":/image/QQ.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);
    painter.drawPixmap(100,400,wechat);
    painter.drawPixmap(500,400,QQ);
}
void MainWindow::on_pushButton_gamestart_clicked(){
    this->hide();
    emit showgamewindow();
}

void MainWindow::on_pushButton_gameoff_clicked(){
    emit quit();
}

void MainWindow::start_show(){
    this->show();
}

