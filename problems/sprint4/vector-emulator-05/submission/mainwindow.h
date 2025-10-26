//
// Created by Kirill "Raaveinm" on 10/25/25.
//

#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void SetRandomGen(const std::mt19937& gen) {
        gen_ = gen;
    }

    [[nodiscard]] const std::mt19937& GetRandomGen() const {
        return gen_;
    }


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
    // Emulator 5
    void on_btn_sort_strict_clicked();
    void on_btn_sort_unstrict_clicked();
    void on_btn_unique_clicked();
    void on_btn_reverse_clicked();
    void on_btn_shuffle_clicked();

private:
    void ApplyModel();
    void ApplyIterator() const;
    Model vector_model_{};
    std::random_device rd_;
    std::mt19937 gen_ = std::mt19937(rd_());
    Ui::MainWindow *ui;
};

template<typename T>
void Sort(std::vector<T> &arr) {
    for (int i = 0; i < arr.size(); ++i) {
        int min = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
    }
}
