#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btn_problem_clicked()
{
    QString text = ui->le_problem->text();
    std::reverse(text.begin(), text.end());
    ui->le_problem->setText(text);
}

