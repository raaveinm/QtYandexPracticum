//
// Created by Kirill "Raaveinm" on 10/25/25.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <iterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(
        ui->list_widget,
        &QListWidget::currentRowChanged,
        this,
        &MainWindow::on_list_widget_currentRowChanged
    );

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    auto preserve_iter = vector_model_.iterator;
    ui->list_widget->blockSignals(true);

    ui->list_widget->clear();
    for (int i = 0; i < vector_model_.items.size(); ++i) {
        ui->list_widget->addItem(
            QString::number(i)
            + QString(": ")
            + QString::fromStdString(vector_model_.items.at(i))
            );
    }
    ui->list_widget->addItem(QString("end"));
    ui->list_widget->blockSignals(false);

    vector_model_.iterator = preserve_iter;

    vector_model_.items.empty()
            ? ui->btn_pop->setDisabled(true)
            : ui->btn_pop->setEnabled(true);

    ui->txt_size->setText(QString::number(vector_model_.items.size()));

    ApplyIterator();
}

void MainWindow::ApplyIterator() const {
    const auto iterator_offset = vector_model_.iterator - vector_model_.items.begin();
    const bool is_end = (vector_model_.iterator == vector_model_.items.end());
    const bool is_first = (vector_model_.iterator == vector_model_.items.begin());

    ui->txt_elem_content->setText(is_end ? "" : QString::fromStdString(*vector_model_.iterator));
    ui->list_widget->blockSignals(true);
    ui->list_widget->setCurrentRow(static_cast<int>(iterator_offset));
    ui->list_widget->blockSignals(false);

    ui->btn_edit->setEnabled(!is_end && !vector_model_.items.empty());
    ui->btn_erase->setEnabled(!is_end);
    ui->btn_next->setEnabled(!is_end);

    ui->btn_prev->setEnabled(!is_first);
}

void MainWindow::on_btn_pop_clicked()
{
    if (!vector_model_.items.empty()) {
        vector_model_.items.pop_back();
        vector_model_.iterator = vector_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_push_clicked()
{
    const QString text = ui->txt_elem_content->text();
    if (!text.isEmpty()) {
        vector_model_.items.push_back(text.toStdString());
        vector_model_.iterator = vector_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_clear_clicked()
{
    vector_model_.items.clear();
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_weekday_clicked()
{
    vector_model_.items = days_of_week;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_month_clicked()
{
    vector_model_.items = months_of_year;
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_prev_clicked()
{
    if (vector_model_.iterator != vector_model_.items.begin()) {
        --vector_model_.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_btn_next_clicked()
{
    if (vector_model_.iterator != vector_model_.items.end()) {
        ++vector_model_.iterator;
        ApplyIterator();
    }
}


void MainWindow::on_btn_begin_clicked()
{
    vector_model_.iterator = vector_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    vector_model_.iterator = vector_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_btn_insert_clicked()
{
    if (const QString text = ui->txt_elem_content->text(); !text.isEmpty()) {
        vector_model_.items.insert(vector_model_.iterator, text.toStdString());
        vector_model_.iterator = vector_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_erase_clicked()
{
    if (vector_model_.iterator != vector_model_.items.end()) {
        vector_model_.items.erase(vector_model_.iterator);
        vector_model_.iterator = vector_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_btn_edit_clicked()
{
    if (vector_model_.iterator != vector_model_.items.end()) {
        const QString t = ui->txt_elem_content->text();
        if (!t.isEmpty()) {
            *vector_model_.iterator = t.toStdString();
            ApplyModel();
        }
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    // vector_model_.iterator = vector_model_.items.begin();
    // std::advance(vector_model_.iterator, currentRow);
    if (currentRow == static_cast<int>(vector_model_.items.size())) {
        vector_model_.iterator = vector_model_.items.end();
    } else {
        vector_model_.iterator = vector_model_.items.begin();
        std::advance(vector_model_.iterator, currentRow);

    }
    ApplyIterator();
}