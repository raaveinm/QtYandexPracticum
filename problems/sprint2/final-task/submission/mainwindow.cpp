#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_memory->setText("");
    ui->l_formula->setText("");
    SetText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString &text)
{
    input_number_ = NormalizeNumber(text);
    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}

void MainWindow::SetOperation(Operation op)
{
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }

    current_operation_ = op;
    QString output_text = QString::number(calculator_.GetNumber())+ QString(" ") + OpToString(current_operation_);
    ui->l_formula->setText(output_text);
    input_number_ = "";
}

QString MainWindow::NormalizeNumber(const QString &text)
{
    if (text.isEmpty()) {
        return "0";
    }
    qsizetype i = 0;
    while (i < text.size() - 1 && text[i] == '0' && text[i+1] != '.') {
        i++;
    }
    return text.mid(i);
}

QString MainWindow::RemoveTrailingZeroes(const QString &text)
{
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        return "0" + text;
    }
    if (text.startsWith('-')) {
        return "-" + RemoveTrailingZeroes(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        // AGENT FIX: This was the source of the infinite recursion.
        return RemoveTrailingZeroes(text.mid(1));
    }
    return text;
}



void MainWindow::on_btn_1_clicked()
{
    AddText("1");
}


void MainWindow::on_btn_2_clicked()
{
    AddText("2");
}


void MainWindow::on_btn_3_clicked()
{
    AddText("3");
}


void MainWindow::on_btn_4_clicked()
{
    AddText("4");
}


void MainWindow::on_btn_5_clicked()
{
    AddText("5");
}


void MainWindow::on_btn_6_clicked()
{
    AddText("6");
}


void MainWindow::on_btn_7_clicked()
{
    AddText("7");
}


void MainWindow::on_btn_8_clicked()
{
    AddText("8");
}


void MainWindow::on_btn_9_clicked()
{
    AddText("9");
}

void MainWindow::on_btn_0_clicked()
{
    AddText("0");
}

void MainWindow::on_btn_dot_clicked()
{
    if (!input_number_.contains(".")) {
        AddText(".");
    }
}


void MainWindow::on_btn_plus_minus_clicked()
{
    // input_number_ = input_number_.startsWith("-")? input_number_.mid(1) : "-" + input_number_;
    // SetText(input_number_);

    if (input_number_.isEmpty()) {
        active_number_ *= -1;
        input_number_ = QString::number(active_number_);
        ui->l_result->setText(input_number_);
    } else {
        input_number_ = input_number_.startsWith("-")? input_number_.mid(1) : "-" + input_number_;
        SetText(input_number_);
    }

}


void MainWindow::on_btn_erase_clicked()
{
    if (!input_number_.isEmpty()) {
        input_number_.chop(1);
        SetText(input_number_);
    }
}

void MainWindow::on_btn_in_pow_clicked()
{
    SetOperation(Operation::POWER);
}


void MainWindow::on_btn_division_clicked()
{
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_btn_multiply_clicked()
{
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_subtract_clicked()
{
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_btn_addition_clicked()
{
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_btn_res_clicked()
{
    if (current_operation_ != Operation::NO_OPERATION) {
        QString output = QString::number(calculator_.GetNumber()) + QString(" ")
        + OpToString(current_operation_) + QString(" ")
            + QString::number(active_number_) + " =";

        ui->l_formula->setText(output);

        switch (current_operation_) {
        case Operation::NO_OPERATION: break;
        case Operation::ADDITION: calculator_.Add(active_number_); break;
        case Operation::DIVISION: calculator_.Div(active_number_); break;
        case Operation::MULTIPLICATION: calculator_.Mul(active_number_); break;
        case Operation::SUBTRACTION: calculator_.Sub(active_number_); break;
        case Operation::POWER: calculator_.Pow(active_number_); break;
        }

        active_number_ = calculator_.GetNumber();
        ui->l_result->setText(QString::number(active_number_));
        input_number_ = "";
        current_operation_ = Operation::NO_OPERATION;
    }
}


void MainWindow::on_btn_clear_clicked()
{
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->setText("");
    SetText("0");
    calculator_.Set(0);
}


void MainWindow::on_btn_ms_clicked()
{
    saved_number_ = active_number_;
    is_saved_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::on_btn_mc_clicked()
{
    saved_number_ = 0.0;
    is_saved_ = false;
    ui->l_memory->setText("");
}

void MainWindow::on_bt_mr_clicked()
{
    if (is_saved_) {
        SetText(QString::number(saved_number_));
        input_number_ = "";
    }
}
