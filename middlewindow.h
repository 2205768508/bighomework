#ifndef MIDDLEWINDOW_H
#define MIDDLEWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>

namespace Ui {
class MiddleWindow;
}

class MiddleWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MiddleWindow(QWidget *parent = 0);
    ~MiddleWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_nextcustom_clicked();
    void on_pushButton_restart_clicked();
    void on_pushButton_gameoff_clicked();
    void middle_show();
signals:
    void showsecondcustom();
    void gobackhome();
    void quit();
private:
    Ui::MiddleWindow *ui;
    QPushButton * button_nextcustom;
    QPushButton * button_restart;
    QPushButton * button_gameoff;
};


#endif // MIDDLEWINDOW_H
