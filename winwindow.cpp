#include "winwindow.h"
#include "ui_winwindow.h"

WinWindow::WinWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WinWindow)
{
    ui->setupUi(this);

    button_home = new QPushButton(this);
    button_gameoff = new QPushButton(this);

    button_home->setGeometry(QRect(362,150,300,200));
    button_home->setIcon(QIcon(QPixmap(":/image/home.png")));
    button_home->setIconSize(QSize(200,200));
    button_home->setFlat(true);

    button_gameoff->setGeometry(QRect(362,350,300,100));
    button_gameoff->setIcon(QIcon(QPixmap(":/image/exit.png")));
    button_gameoff->setIconSize(QSize(200,100));
    button_gameoff->setFlat(true);
    connect(button_home,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_home_clicked()));
    connect(button_gameoff,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_gameoff_clicked()));

}

WinWindow::~WinWindow()
{
    delete ui;
}
void WinWindow::paintEvent(QPaintEvent *){
    QPixmap background(":/image/bg_4.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);

    QPixmap kuang(":/image/dialog.png");
    painter.drawPixmap(0, 518,kuang);
    QPixmap woman(":/image/woman.png");
    painter.drawPixmap(555, 296, woman);
    painter.setPen(QColor(0, 160, 230));

        // 设置字体：微软雅黑、点大小50、斜体
    QRectF rect(50, 518, 552, 250);
    QFont font;
    painter.setPen(QColor(Qt::white));
    font.setFamily("Microsoft YaHei");
    font.setPointSize(10);
    //font.setItalic(true);
    painter.setFont(font);

        // 绘制文本
    painter.drawText(rect, Qt::AlignCenter, "恭喜你，指挥官！你带领人类取得了胜利！");
}
void WinWindow::on_pushButton_home_clicked(){
    this->hide();
    emit gobackhome();
}

void WinWindow::on_pushButton_gameoff_clicked(){
    emit quit();
}

void WinWindow::Win_show(){
    this->show();
}
