#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIntValidator>
#include "magic_horoscope.h"

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

void MainWindow::on_rb_eastern_clicked(bool checked)
{
    CalendarRecomposition(ui->le_year->text());
}


void MainWindow::on_rb_tibetan_clicked(bool checked)
{
    CalendarRecomposition(ui->le_year->text());
}


void MainWindow::on_rb_zoroastrian_clicked(bool checked)
{
    CalendarRecomposition(ui->le_year->text());
}


void MainWindow::on_cb_is_date_clicked(bool checked)
{
    ui->wd_horoscope->setEnabled(checked);
    ui->gb_horoscope->setEnabled(checked);
    HoroscopeRecomposition();
}


void MainWindow::on_sb_day_valueChanged(int arg1)
{
    HoroscopeRecomposition();
}

void MainWindow::on_cb_month_currentIndexChanged(int index)
{
    HoroscopeRecomposition();
}

void MainWindow::on_rb_zodiac_clicked()
{
    HoroscopeRecomposition();
}


void MainWindow::on_rb_druid_clicked()
{
    HoroscopeRecomposition();
}


void MainWindow::on_le_year_textChanged(const QString &arg1)
{
    CalendarRecomposition(arg1);
    HoroscopeRecomposition();
}


void MainWindow::CalendarRecomposition(QString year) {
    QString out = year + " — это год ";
    if (ui->le_year->text().isEmpty()) {
        ui->lbl_calendar->setText("Введите год");
    } else if (ui->rb_eastern->isChecked()) {
        ui->lbl_calendar->setText(out + GetAnimalForEasternCalendar(year.toInt()) + ". Стихия/цвет — "
                                  + GetElementForEasternCalendar(year.toInt()));
    } else if (ui->rb_zoroastrian->isChecked()) {
        ui->lbl_calendar->setText(out + GetAnimalForZoroastrianCalendar(year.toInt()));
    } else {
        ui->lbl_calendar->setText(out + GetAnimalForTibetanCalendar(year.toInt()));
    }
}

void MainWindow::HoroscopeRecomposition()
{
    if(!ui->cb_is_date->isChecked()) {
        ui->lbl_horoscope->setText("Ввод даты отключён");
        return;
    }

    int day = ui->sb_day->value();
    int month = ui->cb_month->currentIndex() + 1;
    int year = ui->le_year->text().toInt();

    if (ui->rb_zodiac->isChecked()) {
        QString zodiac_sign = GetZodiac(day, month, year);
        if (zodiac_sign.isEmpty()) {
            ui->lbl_horoscope->setText("Такой даты не существует");
        } else {
            ui->lbl_horoscope->setText(
                QString("%1.%2 — ваш знак зодиака %3 по зодиакальному гороскопу")
                    .arg(day, 2, 10, QChar('0'))
                    .arg(month, 2, 10, QChar('0'))
                    .arg(zodiac_sign));
        }
    } else {
        QString tree_sign = GetTree(day, month, year);
        if (tree_sign.isEmpty()) {
            ui->lbl_horoscope->setText("Такой даты не существует");
        } else {
            ui->lbl_horoscope->setText(
                QString("%1.%2 — ваше тотемное дерево %3 по гороскопу друидов")
                    .arg(day, 2, 10, QChar('0'))
                    .arg(month, 2, 10, QChar('0'))
                    .arg(tree_sign));
        }
    }
}