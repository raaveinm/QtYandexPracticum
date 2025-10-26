#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() const {
    ui->list_widget->clear();
    for (int i = 0; i < vector_model_.items.size(); ++i) {
        ui->list_widget->addItem(
            QString::number(i)
            + QString(": ")
            + QString::fromStdString(vector_model_.items.at(i))
            );
    }

    vector_model_.items.empty()
            ? ui->btn_pop->setDisabled(true)
            : ui->btn_pop->setEnabled(true);

    ui->txt_size->setText(QString::number(vector_model_.items.size()));
}
void MainWindow::on_btn_pop_clicked()
{
    vector_model_.items.pop_back();
    ApplyModel();
}


void MainWindow::on_btn_push_clicked()
{
    const QString text = ui->txt_elem_content->text();
    if (!text.isEmpty()) {
        vector_model_.items.push_back(text.toStdString());
    }
    ApplyModel();
}


void MainWindow::on_btn_clear_clicked()
{
    vector_model_.items.clear();
    ApplyModel();
}


void MainWindow::on_btn_weekday_clicked()
{
    vector_model_.items = days_of_week;
    ApplyModel();
}


void MainWindow::on_btn_month_clicked()
{
    vector_model_.items = months_of_year;
    ApplyModel();
}

void MainWindow::on_btn_prev_clicked()
{

}


void MainWindow::on_btn_next_clicked()
{

}


void MainWindow::on_btn_begin_clicked()
{

}


void MainWindow::on_btn_end_clicked()
{

}


void MainWindow::on_btn_insert_clicked()
{

}


void MainWindow::on_btn_erase_clicked()
{

}


void MainWindow::on_btn_edit_clicked()
{

}

