#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QFileInfo>
#include <QDir>
#include <QUrl>

QString TimeToString(QTime time) {
    return QString("%1:%2:%3").arg(time.hour(), 2, 10, QChar('0')).arg(time.minute(), 2, 10, QChar('0')).arg(time.second(), 2, 10, QChar('0'));
}

QString TimeToString(std::chrono::milliseconds ms) {
    return TimeToString(QTime::fromMSecsSinceStartOfDay(ms.count() + 500));
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , audio_output_{this}
{
    ui->setupUi(this);
    connect(&timer, &prac::QTimer::timeout, this, &MainWindow::OnTimer);
    connect(ui->action_load_file, &QAction::triggered, this, &MainWindow::on_action_load_file_triggered);

    player_.setAudioOutput(&audio_output_);

    auto current_time = prac::QTime::currentTime();
    ui->lbl_now->setText(TimeToString(current_time));
    timer.start(1000 - current_time.msec());
    Alarm();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Alarm() {
    if (alarm_moment_ == QDateTime{}) {
        ui->lbl_timeout->setText("Установите будильник");
        return;
    }

    auto now_dt = prac::QDateTime::currentDateTime();

    if (alarm_moment_ <= now_dt) {
        ui->lbl_timeout->setText("Пора вставать");
        if (player_.playbackState() != QMediaPlayer::PlaybackState::PlayingState) {
            player_.play();
        }
    } else {
        auto time_to_alarm_ms = now_dt.msecsTo(alarm_moment_);
        ui->lbl_timeout->setText(TimeToString(std::chrono::milliseconds(time_to_alarm_ms)));
    }
}

void MainWindow::OnTimer()
{
    auto current_time = prac::QTime::currentTime();
    ui->lbl_now->setText(TimeToString(current_time));
    timer.start(1000 - current_time.msec());
    Alarm();
}

void MainWindow::on_pb_start_stop_clicked()
{
    if (alarm_moment_ != QDateTime{}) {
        alarm_moment_ = QDateTime{};
        ui->pb_start_stop->setText("Старт");
        player_.stop();
    } else {
        auto now_dt = prac::QDateTime::currentDateTime();
        QTime alarm_time(ui->sb_hour->value(), ui->sb_min->value(), ui->sb_sec->value());
        alarm_moment_ = QDateTime(now_dt.date(), alarm_time);

        if (alarm_moment_ < now_dt) {
            alarm_moment_ = alarm_moment_.addDays(1);
        }

        ui->pb_start_stop->setText("Стоп");
    }
    Alarm();
}

void MainWindow::on_action_load_file_triggered()
{
    QString file_name = prac::QFileDialog::getOpenFileName(this,
                            QString::fromUtf8("Открыть файл"),
                            QDir::currentPath(),
                            "*.wav;*.mp3");
    if (!file_name.isEmpty()) {
        player_.setSource(QUrl::fromLocalFile(file_name));
        ui->lbl_melody->setText(QFileInfo(file_name).fileName());
    }
}
