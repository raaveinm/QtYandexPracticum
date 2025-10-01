#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_le_input_name_textChanged(const QString &arg1)
{
    QString name = ui->le_input_name->text();
    if (name.isEmpty()) {
        ui->lbl_result->setText("Введите имя");
    } else {
        ui->lbl_result->setText("Привет из Qt, "+ name + "!");
    }
}

