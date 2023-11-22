#include "home.h"
#include "ui_home.h"
#include <QMessageBox>
#include <string.h>
#include <QDebug>

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    led_flag = 0;
    speak_flag = 0;

    serialport = new QSerialPort;

    connect(serialport, &QSerialPort::readyRead, this, &Home::slot_readserialport);
}

Home::~Home()
{
    delete ui;
    delete serialport;
}

void Home::on_pushButton_clicked()
{
    emit signal_return();
}



void Home::on_pushButton_8_clicked()
{
    //用于通信的端口名称
    serialport->setPortName(ui->lineEdit->text());
    serialport->setBaudRate(QSerialPort::Baud115200);
    serialport->setDataBits(QSerialPort::Data8);
    serialport->setParity(QSerialPort::NoParity);
    serialport->setStopBits(QSerialPort::OneStop);
    serialport->setFlowControl(QSerialPort::NoFlowControl);

    if (serialport->open(QIODevice::ReadWrite) == false)
    {
        QMessageBox::warning(this, "警告", "串口打开失败");
    }
    else
    {
        ui->textBrowser->insertPlainText("串口打开成功\n");
    }

}


void Home::slot_readserialport() //通过判断串口的返回值从而才显示屏上显示不同的内容
{
    char return_value = 0;
    serialport->read(&return_value, 1);
    switch (return_value) {
    case '0':
        ui->textBrowser->insertPlainText("灯已关闭\r\n");
        break;
    case '1':
        ui->textBrowser->insertPlainText("灯已打开\r\n");
        break;
    case '3':
        ui->textBrowser->insertPlainText("音响已关闭\r\n");
        break;
    case '4':
        ui->textBrowser->insertPlainText("音响已打开\r\n");
        break;
    case '5':
        ui->textBrowser->insertPlainText("空调已打开\r\n");
        break;
    case '6':
        ui->textBrowser->insertPlainText("空调已关闭\r\n");
        break;
    default:
        break;
    }

}


void Home::on_pushButton_2_clicked()
{
    int static led=1;
    int static led_number_press=0;
    led=led+1;
    led_number_press=led%2;//通过取余方式判断第几次按按钮，如果是单数按余数就为0对应开启，双数按余数位1代表关闭
    if(led_number_press==0)
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x00;//对小灯进行操作
        buf.text = 0x01;//打开小灯
        serialport->write((char *)&buf, sizeof(buf));
        qDebug() << "send:" << (int)buf.addr << (int)buf.func << (int)buf.peripheral << (int)buf.text;
        ui->pushButton_2->setStyleSheet("#pushButton_2{border-image: url(:/image/开灯.png);}"
                                        "#pushButton_2{background-image: url(:/image/background.png);}");
    }
    else
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x00;//对小灯进行操作
        buf.text = 0x00;//关闭小灯
        serialport->write((char *)&buf, sizeof(buf));
        ui->pushButton_2->setStyleSheet("#pushButton_2{border-image: url(:/image/关灯.png);}"
                                        "#pushButton_2{background-image: url(:/image/background.png);}");
    }
}

void Home::on_pushButton_4_clicked()
{
    int static led=1;
    int static led_number_press=0;
    led=led+1;
    led_number_press=led%2;//通过取余方式判断第几次按按钮，如果是单数按余数就为0对应开启，双数按余数位1代表关闭
    if(led_number_press==0)
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x01;//蜂鸣器进行操作
        buf.text = 0x01;//打开蜂鸣器
        serialport->write((char *)&buf, sizeof(buf));//发送数据
        qDebug() << "send:" << (int)buf.addr << (int)buf.func << (int)buf.peripheral << (int)buf.text;
        ui->pushButton_4->setStyleSheet("#pushButton_4{border-image: url(:/image/音响 (1).png);}"
                                        "#pushButton_4{background-image: url(:/image/background.png);}");
    }
    else
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x01;//对蜂鸣器进行操作
        buf.text = 0x00;//关闭蜂鸣器
        serialport->write((char *)&buf, sizeof(buf));//发送数据
        ui->pushButton_4->setStyleSheet("#pushButton_4{border-image: url(:/image/音响.png);}"
                                        "#pushButton_4{background-image: url(:/image/background.png);}");

    }
}

void Home::on_pushButton_3_clicked()
{
    int static led=1;
    int static led_number_press=0;
    led=led+1;
    led_number_press=led%2;//通过取余方式判断第几次按按钮，如果是单数按余数就为0对应开启，双数按余数位1代表关闭
    if(led_number_press==0)
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x02;//空调进行操作
        buf.text = 0x01;//打开空调
        serialport->write((char *)&buf, sizeof(buf));//发送数据
        qDebug() << "send:" << (int)buf.addr << (int)buf.func << (int)buf.peripheral << (int)buf.text;
        ui->pushButton_3->setStyleSheet("#pushButton_3{border-image: url(:/image/空调1.png);}"
                                        "#pushButton_3{background-image: url(:/image/background.png);}");

    }
    else
    {
        Datatype buf;
        memset(&buf, 0, sizeof(buf));
        buf.addr = 0x00;//表示开发板
        buf.func = 0x01;//写数据
        buf.peripheral = 0x02;//对空调进行操作
        buf.text = 0x00;//关闭空调
        serialport->write((char *)&buf, sizeof(buf));//发送数据
        ui->pushButton_3->setStyleSheet("#pushButton_3{border-image: url(:/image/空调2.png);}"
                                        "#pushButton_3{background-image: url(:/image/background.png);}");
    }
}
