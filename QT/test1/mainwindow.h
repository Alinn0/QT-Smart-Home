#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <home.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void slot_test(QString id, QString secret);

    void slot_return();

signals:
    void signal_test(QString id, QString secret);

private:
    Ui::MainWindow *ui;

    Home *h;
};

#endif // MAINWINDOW_H
