//
// Created by Kirill "Raaveinm" on 10/25/25.
//

#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Emulator 1
    void on_btn_pop_clicked();
    void on_btn_push_clicked();
    void on_btn_clear_clicked();
    void on_btn_weekday_clicked();
    void on_btn_month_clicked();
    void on_btn_prev_clicked();
    void on_btn_next_clicked();
    void on_btn_begin_clicked();
    void on_btn_end_clicked();
    void on_btn_insert_clicked();
    void on_btn_erase_clicked();
    void on_btn_edit_clicked();
    // Emulator 2
    void on_list_widget_currentRowChanged(int currentRow);
    // Emulator 3
    void on_btn_capacity_clicked();
    void on_btn_resize_clicked();
    // Emulator 4
    void on_btn_max_elem_clicked();
    void on_btn_min_elem_clicked();
    void on_btn_find_clicked();
    void on_btn_count_clicked();
    void on_btn_sort_strict_clicked();
    void on_btn_sort_unstrict_clicked();
    void on_btn_unique_clicked();
    void on_btn_reverse_clicked();
    void on_btn_shuffle_clicked();

private:
    void ApplyModel();
    void ApplyIterator() const;

private:
    Model vector_model_;
    Ui::MainWindow *ui;
};
