#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //h = new Home;
    h = NULL;

    //手动连接信号与槽函数
    connect(this, &MainWindow::signal_test, this, &MainWindow::slot_test);

    //connect(h, &Home::signal_return, this, &MainWindow::slot_return);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
    //发送测试信号
    emit signal_test(ui->lineEdit_id->text(), ui->lineEdit_secret->text());
}

void MainWindow::slot_test(QString id, QString secret)
{
    if (id == "l" && secret == "n")
    {
//        qDebug() << "slot_test()";
//        qDebug() << id << secret;
        if (NULL == h)
        {
            h = new Home;
            connect(h, &Home::signal_return, this, &MainWindow::slot_return);

            h->show();
            this->close();
        }
    }
    else
    {
        QMessageBox::warning(this, "警告", "账号和密码错误");
        qDebug() << "账号或密码错误";
    }
}

void MainWindow::slot_return()
{
    this->show();
    h->close();

    delete h;
    h = NULL;
}
