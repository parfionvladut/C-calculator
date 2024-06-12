#include "mainwindow.h"
#include "qdialog.h"
#include "ui_mainwindow.h"
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"

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


void MainWindow::on_pushButton_clicked()
{
    Dialog1 dialog1;
    dialog1.setModal(true);
    MainWindow::hide();
    dialog1.exec();
    MainWindow::show();
}


void MainWindow::on_pushButton_2_clicked()
{
    Dialog2 thirddialog;
    thirddialog.setModal(true);
    MainWindow::hide();
    thirddialog.exec();
    MainWindow::show();
}


void MainWindow::on_pushButton_3_clicked()
{
    Dialog3 thirddialog;
    thirddialog.setModal(true);
    MainWindow::hide();
    thirddialog.exec();
    MainWindow::show();
}

