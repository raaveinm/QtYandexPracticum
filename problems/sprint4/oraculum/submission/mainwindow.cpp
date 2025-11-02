#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Reset();
    ShowQuestion();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Reset() {
    a_ = 0;
    b_ = 101;
    m_ = (a_ + b_) / 2;
}

void MainWindow::ShowQuestion() {
    // Показываем вопрос, используя ui->lbl_question->setText.
    // Если b_ - a_ <= 1, то мы угадали. Нужно показать не вопрос,
    // а ответ.
    const QString txt = b_ - a_ > 1
            ? "Ваше число меньше " + QString::number(m_) + "?"
            : "Ваше число " + QString::number(a_) + "!";
    ui->lbl_question->setText(txt);
}

void MainWindow::on_btn_yes_clicked() {
    if (b_ - a_ <= 1) {
        Reset();
        ShowQuestion();
        return;
    }
    b_ = m_;
    m_ = (a_ + b_) / 2;
    ShowQuestion();
}

void MainWindow::on_btn_no_clicked() {
    if (b_ - a_ <= 1) {
        Reset();
        ShowQuestion();
        return;
    }
    a_ = m_;
    m_ = (a_ + b_) / 2;
    ShowQuestion();
}
