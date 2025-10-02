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
    ui->gb_horoscope->setEnabled(checked);
    ui->cb_month->setEnabled(checked);
    ui->label_2->setEnabled(checked);
    ui->label_3->setEnabled(checked);
    ui->sb_day->setEnabled(checked);
    HoroscopeRecomposition();
}


void MainWindow::on_sb_day_valueChanged(int arg1)
{
    int month = ui->cb_month->currentIndex() + 1;

}


void MainWindow::on_cb_month_editTextChanged(const QString &arg1)
{

}

/*
    // Получение символа года по восточному календарю.
    QString GetAnimalForEasternCalendar(int year);

    // Получение стихии года по восточному календарю.
    QString GetElementForEasternCalendar(int year);

    // Получение символа года по тибетскому календарю.
    QString GetAnimalForTibetanCalendar(int year);

    // Получение символа года по зороастрийскому календарю.
    QString GetAnimalForZoroastrianCalendar(int year);

    // Получение знака зодиака.
    QString GetZodiac(int day, int month, int year);

    // Получение названия тотемного дерева.
    QString GetTree(int day, int month, int year);
*/

void MainWindow::on_le_year_textChanged(const QString &arg1)
{
    CalendarRecomposition(arg1);
}


void MainWindow::CalendarRecomposition(QString year) {
    QString out = year + " — это год ";
    if (ui->le_year->text().isEmpty()) {
        ui->lbl_calendar->setText("Введите год");
    } else if (ui->rb_eastern->isChecked()) {
        ui->lbl_calendar->setText(out + GetAnimalForEasternCalendar(year.toInt()) + ". Стихия/цвет — " + GetElementForEasternCalendar(year.toInt()));
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
}


