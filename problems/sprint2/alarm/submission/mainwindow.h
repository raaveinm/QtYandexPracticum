#pragma once

#include <QMainWindow>
#include <prac/QTimer>
#include <prac/QMediaPlayer>
#include <prac/QTime>
#include <prac/QDateTime>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDateTime GetAlarmMoment() const {
        return alarm_moment_;
    }

private:
    void Alarm();

private slots:
    void OnTimer();

    void on_pb_start_stop_clicked();
    void on_action_load_file_triggered();

private:
    Ui::MainWindow *ui;
    QDateTime alarm_moment_;
    prac::QTimer timer{this};
    prac::QMediaPlayer player_;
    QAudioOutput audio_output_{this};
};
