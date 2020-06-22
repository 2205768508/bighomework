#ifndef LOSTWINDOW_H
#define LOSTWINDOW_H


#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>

namespace Ui {
class LostWindow;
}

class LostWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LostWindow(QWidget *parent = 0);
    ~LostWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_home_clicked();
    void on_pushButton_restart_clicked();
    void on_pushButton_gameoff_clicked();
    void lost_show();
signals:
    void gobackhome();
    void showmainwindow();
    void quit();
private:
    Ui::LostWindow *ui;
    QPushButton *button_home;
    QPushButton *button_gameoff;
    QPushButton *button_restart;

};

#endif // LOSTWINDOW_H
