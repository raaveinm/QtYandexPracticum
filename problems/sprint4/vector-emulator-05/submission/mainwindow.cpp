//
// Created by Kirill "Raaveinm" on 10/25/25.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include <algorithm>
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
    const auto preserve_iter = vector_model_.iterator;
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
    ui->txt_capacity->setText(QString::number(vector_model_.items.capacity()));

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
void MainWindow::on_btn_capacity_clicked() {
    const int capacity = ui->txt_capacity->text().toInt();
    vector_model_.items.reserve(capacity);
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_resize_clicked() {
    const int size = ui->txt_size->text().toInt();
    vector_model_.items.resize(size);
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_max_elem_clicked() {
    vector_model_.iterator = std::max_element(
        vector_model_.items.begin(),
        vector_model_.items.end());

    ApplyIterator();
}


void MainWindow::on_btn_min_elem_clicked() {
    vector_model_.iterator = std::min_element(
        vector_model_.items.begin(),
        vector_model_.items.end());

    ApplyIterator();
}


void MainWindow::on_btn_find_clicked() {
    const std::string text = ui->txt_elem_content->text().toStdString();
    vector_model_.iterator = std::find(
        vector_model_.items.begin(),
        vector_model_.items.end(),
        text);
    ApplyIterator();
}


void MainWindow::on_btn_count_clicked() {
    const std::string element = ui->le_count->text().toStdString();
    const auto count = std::count(vector_model_.items.begin(), vector_model_.items.end(), element);
    ui->lbl_count->setText(QString::number(count));
}

void MainWindow::on_btn_sort_strict_clicked() {
    Sort(vector_model_.items);
    ApplyModel();
}


void MainWindow::on_btn_sort_unstrict_clicked() {
    std::ranges::sort(vector_model_.items,
                      [](const std::string& a, const std::string& b) {
                          return std::ranges::lexicographical_compare(a, b,
                              [](const unsigned char c1, const unsigned char c2) {
                                  return std::tolower(c1) < std::tolower(c2);
                          });
                      });

    ApplyModel();
}


void MainWindow::on_btn_unique_clicked() {
    if (!std::is_sorted(vector_model_.items.begin(), vector_model_.items.end())) { return; }
    const auto to_del = std::unique(vector_model_.items.begin(), vector_model_.items.end());
    vector_model_.items.erase(to_del, vector_model_.items.end());
    vector_model_.iterator = vector_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_reverse_clicked() {
    std::ranges::reverse(vector_model_.items);
    ApplyModel();
}


void MainWindow::on_btn_shuffle_clicked() {
    std::ranges::shuffle(vector_model_.items, gen_);
    ApplyModel();
}
