#pragma once

#include "calculator.h"
#include "ui_mainwindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();


private slots:

    void on_btn_1_clicked();

    void on_btn_2_clicked();

    void on_btn_3_clicked();

    void on_btn_4_clicked();

    void on_btn_5_clicked();

    void on_btn_6_clicked();

    void on_btn_7_clicked();

    void on_btn_8_clicked();

    void on_btn_9_clicked();

    void on_btn_0_clicked();

    void on_btn_dot_clicked();

    void on_btn_erase_clicked();

    void on_btn_plus_minus_clicked();

    void on_btn_in_pow_clicked();

    void on_btn_division_clicked();

    void on_btn_multiply_clicked();

    void on_btn_subtract_clicked();

    void on_btn_addition_clicked();

    void on_btn_res_clicked();

    void on_btn_clear_clicked();

    void on_btn_ms_clicked();

    void on_btn_mc_clicked();

    void on_bt_mr_clicked();


private:
    Ui::MainWindow* ui;
    Calculator calculator_;
    QString input_number_;
	double active_number_;
    bool is_saved_ = false;
    double saved_number_;
    Operation current_operation_ = Operation::NO_OPERATION;

    QString NormalizeNumber(const QString &text);

    QString RemoveTrailingZeroes(const QString &text);

    void SetText(const QString& text);

    inline void AddText(const QString& suffix){
        input_number_ += suffix;
        SetText(input_number_);
    }

    void SetOperation(Operation op);

    inline QString OpToString(Operation op) {
        switch(op) {
        case Operation::NO_OPERATION: return "";
        case Operation::ADDITION: return "+";
        case Operation::DIVISION: return "÷";
        case Operation::MULTIPLICATION: return "×";
        case Operation::SUBTRACTION: return "−";
        case Operation::POWER: return "^";
        }
    }
};
