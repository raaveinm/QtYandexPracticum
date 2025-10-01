#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    UpdateSizeLabel();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateSizeLabel() {
    ui->lbl_size->move(0,0);
    auto new_text = std::to_string(width()) + "x" + std::to_string(height());
    // std::cout << new_text << std::endl;
    ui->lbl_size->setFixedSize(width(),height());
    ui->lbl_size->setText(QString::fromStdString(new_text));
}
