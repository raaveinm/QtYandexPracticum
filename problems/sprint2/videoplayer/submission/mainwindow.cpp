#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <prac/QFileDialog>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player_.setVideoOutput(ui->video_output);
    player_.setAudioOutput(&audio_output_);

    connect(&player_, &prac::QMediaPlayer::positionChanged, this, &MainWindow::on_position_changed);
    connect(&player_, &prac::QMediaPlayer::mediaStatusChanged, this, &MainWindow::on_media_status_changed);
    connect(&player_, &prac::QMediaPlayer::playbackStateChanged, this, &MainWindow::on_playback_state_changed);

    UpdatePlayButton();

    audio_output_.setVolume(1.f);
}

void MainWindow::on_position_changed(qint64 position) {
    if (!position_changing_){
        ui->sld_pos->setValue(position);
    }
}

void MainWindow::on_media_status_changed(QMediaPlayer::MediaStatus) {
    int duration = player_.duration();
    ui->sld_pos->setMaximum(duration);
    UpdatePlayButton();
}

void MainWindow::on_playback_state_changed(QMediaPlayer::PlaybackState new_state) {
    UpdatePlayButton();
}

void MainWindow::on_btn_choose_clicked()
{
    QString path = prac::QFileDialog::getOpenFileName(this,
                                       QString("Pick Video"));

    player_.setSource(QUrl::fromLocalFile(path));
    player_.play();
    UpdatePlayButton();
}

void MainWindow::on_btn_pause_clicked()
{
    if (player_.playbackState() == QMediaPlayer::PlaybackState::PausedState) {
        player_.play();
    } else if (player_.playbackState() == QMediaPlayer::PlaybackState::StoppedState) {
        player_.setPosition(0);
        player_.play();
    } else if (player_.playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        player_.pause();
    }

}

void MainWindow::on_sld_volume_valueChanged(int value)
{
    audio_output_.setVolume(value/100.);
}

void MainWindow::on_sld_pos_valueChanged(int value)
{
    position_changing_ = true;
    player_.setPosition(value);
    position_changing_ = false;
}

void MainWindow::UpdatePlayButton()
{
    if (player_.playbackState() == QMediaPlayer::PlaybackState::PlayingState) {
        ui->btn_pause->setText("⏸");
    } else {
        ui->btn_pause->setText("⏵");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
