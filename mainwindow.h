#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent *);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_gamestart_clicked();
    void on_pushButton_gameoff_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *button_gamestart;
    QPushButton *button_gameoff;
};
#endif // MAINWINDOW_H
