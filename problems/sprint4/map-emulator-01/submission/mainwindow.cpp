#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->list_widget, &QListWidget::currentRowChanged, this, &MainWindow::on_list_widget_currentRowChanged);
    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow >= 0 && currentRow < map_model_.items.size()) {
        auto it = map_model_.items.begin();
        std::advance(it, currentRow);
        map_model_.iterator = it;
    } else {
        map_model_.iterator = map_model_.items.end();
    }
    ApplyIterator();
}

void MainWindow::ApplyModel() {
    ui->list_widget->blockSignals(true);

    ui->list_widget->clear();
    for (const auto& [fst, snd] : map_model_.items) {
        ui->list_widget->addItem(QString::fromStdString(fst)
                                 + QString(": ")
                                 + QString::fromStdString(snd));
    }
    ui->list_widget->addItem(QString("end"));
    ui->list_widget->blockSignals(false);
    map_model_.items.empty() ?
            ui->btn_clear->setDisabled(true) :
            ui->btn_clear->setDisabled(false);
    ui->txt_size->setText(QString::number(map_model_.items.size()));
    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    const bool is_end = (map_model_.iterator == map_model_.items.end());
    const auto it_offset = is_end ? map_model_.items.size() : std::distance(map_model_.items.begin(), map_model_.iterator);
    const bool is_first = (map_model_.iterator == map_model_.items.begin());

    ui->txt_elem_key->setText(is_end ? "" : QString::fromStdString(map_model_.iterator->first));
    ui->txt_elem_value->setText(is_end ? "" : QString::fromStdString(map_model_.iterator->second));
    ui->list_widget->blockSignals(true);
    ui->list_widget->setCurrentRow(static_cast<int>(it_offset));
    ui->list_widget->blockSignals(false);
    ui->btn_erase->setDisabled(is_end);
    ui->btn_clear->setDisabled(map_model_.items.empty());
    ui->btn_inc_iterator->setDisabled(is_end);
    ui->btn_dec_iterator->setDisabled(is_first);
}

void MainWindow::on_btn_set_by_key_clicked() {
    const std::string key = ui->txt_elem_key->text().toStdString();
    const std::string value = ui->txt_elem_value->text().toStdString();
    map_model_.items[key] = value;
    ApplyModel();
}


void MainWindow::on_btn_clear_clicked() {
    map_model_.items.clear();
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_erase_clicked() {
    if (map_model_.iterator != map_model_.items.end()) {
        map_model_.items.erase(map_model_.iterator);
        map_model_.iterator = map_model_.items.begin();
    }
    ApplyModel();
}


void MainWindow::on_btn_find_clicked() {
    const std::string key = ui->txt_elem_key->text().toStdString();
    map_model_.iterator = map_model_.items.find(key);
    ApplyIterator();
}


void MainWindow::on_btn_dec_iterator_clicked() {
    if (map_model_.iterator != map_model_.items.begin()) {
        --map_model_.iterator;
    }
    ApplyIterator();
}


void MainWindow::on_btn_inc_iterator_clicked()
{
    if (map_model_.iterator != map_model_.items.end()) {
        ++map_model_.iterator;
    }
    ApplyIterator();
}


void MainWindow::on_btn_begin_clicked()
{
    map_model_.iterator = map_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_btn_end_clicked()
{
    map_model_.iterator = map_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_books_clicked()
{
    map_model_.items.insert(authors_and_books.begin(), authors_and_books.end());
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_btn_words_clicked()
{
    map_model_.items.insert(words.begin(), words.end());
    map_model_.iterator = map_model_.items.begin();
    ApplyModel();
}
