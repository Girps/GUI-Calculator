#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Tokenizer.h"
#include "Parser.h"
#include <Qstring>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*
    Void function when btn 0 is pressed add 0 to the line box for evaluation
*/
void MainWindow::on_pushBtn_Zero_clicked()
{
    QString result = ui->Line_Output->text();
    // Now concatenate 0 to the text
    result += "0";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_One_clicked()
{
    QString result = ui->Line_Output->text();
    result += "1";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Two_clicked()
{
    QString result = ui->Line_Output->text();
    result += "2";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Three_clicked()
{
    QString result = ui->Line_Output->text();
    result += "3";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Four_clicked()
{
    QString result = ui->Line_Output->text();
    result += "4";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Five_clicked()
{
    QString result = ui->Line_Output->text();
    result += "5";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Six_clicked()
{
    QString result = ui->Line_Output->text();
    result += "6";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Seven_clicked()
{
    QString result = ui->Line_Output->text();
    result += "7";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Eight_clicked()
{
    QString result = ui->Line_Output->text();
    result += "8";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Nine_clicked()
{
    QString result = ui->Line_Output->text();
    result += "9";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Cancel_clicked()
{
    ui->Line_Output->clear();
}


void MainWindow::on_pushBtn_LeftParen_clicked()
{
    QString result = ui->Line_Output->text();
    result += "(";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_RightParen_clicked()
{
    QString result = ui->Line_Output->text();
    result += ")";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Multiply_clicked()
{
    QString result = ui->Line_Output->text();
    result += "*";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Exponent_clicked()
{
    QString result = ui->Line_Output->text();
    result += "^";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Divide_clicked()
{
    QString result = ui->Line_Output->text();
    result += "/";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Plus_clicked()
{
    QString result = ui->Line_Output->text();
    result += "+";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Minus_clicked()
{
    QString result = ui->Line_Output->text();
    result += "-";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushBtn_Dot_clicked()
{
    QString result = ui->Line_Output->text();
    result += ".";
    ui->Line_Output->setText(result);
}


void MainWindow::on_pushButton_Cancel_clicked()
{
    QString result = ui->Line_Output->text();
    result = result.removeLast();
    ui->Line_Output->setText(result);
}


/*
    Void enter function reads the expression from the line
    and uses a class to tokenize each character and parses
    it into a valid expression returns result back to line
*/
void MainWindow::on_pushBtn_Enter_clicked()
{
    QString result = ui->Line_Output->text();

    try
    {
        Tokenizer t(result.toStdString());  // convert to String process tokens
        Parser p(t.getStack());
        std::string res = std::to_string(p.getResult());
        result = result.fromStdString(res);
        ui->Line_Output->setText(result);
    }
    catch(std::exception &e)    // Tokenizer or Parsing error
    {
        std::string err (e.what());
        result = result.fromStdString(err);
        ui->Line_Output->setText(result);
    }
}

