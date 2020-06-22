#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>

namespace Ui {
class WinWindow;
}

class WinWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit WinWindow(QWidget *parent = 0);
    ~WinWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_home_clicked();
    void on_pushButton_gameoff_clicked();
    void Win_show();
signals:
    void gobackhome();
    void quit();
private:
    Ui::WinWindow *ui;
    QPushButton *button_home;
    QPushButton *button_gameoff;
};

#endif // WINWINDOW_H
