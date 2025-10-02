
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

int DaysPerMonth(int month, int year) {
    if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            return 29;
        } else {
            return 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

int CalculateDaysFromStartYear(int day, int month, int year) {
    if (month == 0) {
        return 0;
    }
    int num_days = 0;
    for (int m = 1; m < month; ++m) {
        num_days += DaysPerMonth(m, year);
    }
    num_days += day;
    return num_days;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->le_day->setValidator(new QIntValidator(1, 31, this));
    ui->le_month->setValidator(new QIntValidator(1, 12, this));
    ui->le_year->setValidator(new QIntValidator(1, 9999, this));

    ui->le_date->setInputMask("00.00.0000");
    SetError("Некорректная дата");
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::GetFormatType1(int day, int month, int year) {
    return QString("%1.%2.%3")
    .arg(day, 2, 10, QChar('0'))
        .arg(month, 2, 10, QChar('0'))
        .arg(year);
}

QString MainWindow::GetFormatType2(int day, int month, int year) {
    return QString("%1/%2/%3")
    .arg(month, 2, 10, QChar('0'))
        .arg(day, 2, 10, QChar('0'))
        .arg(year);
}

QString MainWindow::GetFormatType3(int day, int month, int year) {
    static const QString monthes[] = {
                                      "января", "февраля", "марта",    "апреля", "мая",      "июня",
                                      "июля",   "августа", "сентября", "октября",  "ноября", "декабря"};
    return QString("%1 %2 %3 года")
        .arg(day, 2, 10, QChar('0'))
        .arg(monthes[month - 1])
        .arg(year);
}

QString MainWindow::GetStrNumDays(int num_days, int year) {
    return QString("Это %1 день в %2 году").arg(num_days).arg(year);
}

void MainWindow::CheckValidity(QLineEdit* elem) {
    bool is_valid = elem->hasAcceptableInput();
    elem->setStyleSheet(is_valid ? "border:1px solid transparent" : "border:1px solid red");
}

void MainWindow::ShowFormattedDate() {
    CheckValidity(ui->le_day);
    CheckValidity(ui->le_month);
    CheckValidity(ui->le_year);

    if (!ui->le_day->hasAcceptableInput() ||
        !ui->le_month->hasAcceptableInput() ||
        !ui->le_year->hasAcceptableInput()) {
        SetError("Некорректная дата");
        return;
    }

    int day = ui->le_day->text().toInt();
    int month = ui->le_month->text().toInt();
    int year = ui->le_year->text().toInt();

    if (day > DaysPerMonth(month, year)) {
        SetError("Такой даты не существует");
    } else {
        ui->lbl_message->clear();

        ui->lbl_format_type1->setText(GetFormatType1(day, month, year));
        ui->lbl_format_type2->setText(GetFormatType2(day, month, year));
        ui->lbl_format_type3->setText(GetFormatType3(day, month, year));

        int num_days = CalculateDaysFromStartYear(day, month, year);
        ui->lbl_message->setText(GetStrNumDays(num_days, year));
    }
}

void MainWindow::SetError(const QString& err_text) {
    ui->lbl_format_type1->clear();
    ui->lbl_format_type2->clear();
    ui->lbl_format_type3->clear();
    ui->lbl_message->setText(err_text);
}

void MainWindow::on_le_date_textChanged(const QString& text) {
    if (editing_now_) {
        return;
    }

    if (ui->le_date->hasAcceptableInput()) {
        ui->le_date->setStyleSheet("border:1px solid transparent");
        QStringList parts = text.split('.');
        if (parts.size() == 3) {
            editing_now_ = true;
            ui->le_day->setText(parts[0]);
            ui->le_month->setText(parts[1]);
            ui->le_year->setText(parts[2]);
            editing_now_ = false;
        }
        ShowFormattedDate();
    } else {
        ui->le_date->setStyleSheet("border:1px solid red");
        SetError("Некорректная дата");
    }
}

void MainWindow::on_le_day_textChanged(const QString&) {
    if (editing_now_) {
        return;
    }
    ShowFormattedDate();
    if (ui->le_day->hasAcceptableInput() && ui->le_month->hasAcceptableInput() && ui->le_year->hasAcceptableInput()) {
        editing_now_ = true;
        ui->le_date->setText(GetFormatType1(ui->le_day->text().toInt(), ui->le_month->text().toInt(), ui->le_year->text().toInt()));
        editing_now_ = false;
    }
}

void MainWindow::on_le_month_textChanged(const QString&) {
    if (editing_now_) {
        return;
    }
    ShowFormattedDate();
    if (ui->le_day->hasAcceptableInput() && ui->le_month->hasAcceptableInput() && ui->le_year->hasAcceptableInput()) {
        editing_now_ = true;
        ui->le_date->setText(GetFormatType1(ui->le_day->text().toInt(), ui->le_month->text().toInt(), ui->le_year->text().toInt()));
        editing_now_ = false;
    }
}

void MainWindow::on_le_year_textChanged(const QString&) {
    if (editing_now_) {
        return;
    }
    ShowFormattedDate();
    if (ui->le_day->hasAcceptableInput() && ui->le_month->hasAcceptableInput() && ui->le_year->hasAcceptableInput()) {
        editing_now_ = true;
        ui->le_date->setText(GetFormatType1(ui->le_day->text().toInt(), ui->le_month->text().toInt(), ui->le_year->text().toInt()));
        editing_now_ = false;
    }
}
