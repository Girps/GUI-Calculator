#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushBtn_Zero_clicked();

    void on_pushBtn_One_clicked();

    void on_pushBtn_Two_clicked();

    void on_pushBtn_Three_clicked();

    void on_pushBtn_Four_clicked();

    void on_pushBtn_Five_clicked();

    void on_pushBtn_Six_clicked();

    void on_pushBtn_Seven_clicked();

    void on_pushBtn_Eight_clicked();

    void on_pushBtn_Nine_clicked();

    void on_pushBtn_Cancel_clicked();

    void on_pushBtn_LeftParen_clicked();

    void on_pushBtn_RightParen_clicked();

    void on_pushBtn_Multiply_clicked();

    void on_pushBtn_Exponent_clicked();

    void on_pushBtn_Divide_clicked();

    void on_pushBtn_Plus_clicked();

    void on_pushBtn_Minus_clicked();

    void on_pushBtn_Dot_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushBtn_Enter_clicked();

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    QPoint currentPos;
    QPoint newPos;
};
#endif // MAINWINDOW_H
