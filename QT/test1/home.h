#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class Home;
}

struct Datatype
{
    //从机地址,这里从机只有一个
    char addr;//0x00
    //功能码：读操作还是写操作
    char func;//0x00读，0x01写
    //读写地址,具体读写什么设备
    char peripheral;//0x00灯
    //读写内容
    char text;//灯:0x00关灯，0x01开灯
};


class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_8_clicked();

    void slot_readserialport();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

signals:

    void signal_return();

private:
    Ui::Home *ui;

    char led_flag;
    char speak_flag;

    QSerialPort *serialport;

};

#endif // HOME_H
