#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rb_asc_clicked()
{
    is_descend = ui->rb_desc->isChecked();
    ui->le_sorted->setText(InitSort(ui->le_unsorted->text()));
}

void MainWindow::on_rb_desc_clicked()
{
    is_descend = ui->rb_desc->isChecked();
    ui->le_sorted->setText(InitSort(ui->le_unsorted->text()));
}

void MainWindow::on_cb_case_clicked()
{
    is_sensetive = ui->cb_case->isChecked();
    ui->le_sorted->setText(InitSort(ui->le_unsorted->text()));
}

void MainWindow::on_le_unsorted_textChanged(const QString&)
{
    ui->le_sorted->setText(InitSort(ui->le_unsorted->text()));
}

QString MainWindow::InitSort(const QString &qs)
{
    QStringList q_word_list = qs.split(' ', Qt::SkipEmptyParts);

    // if (is_sensetive){
    //     std::vector<std::string> words;
    //     for (QString word : q_word_list) {
    //         words.push_back(word.toStdString());
    //     }
    //     return SortWords(words, is_descend);

    // } else {
    //     std::vector<QString> words;
    //     for(QString word: q_word_list) {
    //         words.push_back(word);
    //     }
    //     return SortWordsInsensetive(words, is_descend);
    // }

    std::vector<QString> words;
    for(QString word: q_word_list) {
        words.push_back(word);
    }
    return SortWordsInsensetive(words, is_descend);
}


QString MainWindow::SortWords(const std::vector<std::string>& v, bool is_desc)
{
    return QString("");
}

QString MainWindow::SortWordsInsensetive(const std::vector<QString> &qs, bool is_desc)
{
    std::vector<QString> sorted_qs = qs;
    if (is_sensetive) {
        std::sort(sorted_qs.begin(), sorted_qs.end(), [is_desc](const QString lhs, const QString rhs){
            if (is_desc){
                return QString::compare(lhs, rhs, Qt::CaseSensitive) > 0;
            } else {
                return QString::compare(lhs, rhs, Qt::CaseSensitive) < 0;
            }
        });
    } else {
        std::sort(sorted_qs.begin(), sorted_qs.end(), [is_desc](const QString lhs, const QString rhs){
            if (is_desc){
                return QString::compare(lhs, rhs, Qt::CaseInsensitive) > 0;
            } else {
                return QString::compare(lhs, rhs, Qt::CaseInsensitive) < 0;
            }
        });
    }
    return QStringList(sorted_qs.begin(), sorted_qs.end()).join(QChar(' '));
}
