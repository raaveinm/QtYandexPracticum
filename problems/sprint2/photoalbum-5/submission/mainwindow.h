#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDir>
#include <prac/QFileDialog>
#include <prac/QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetPixmap(const QString path) {
        active_pixmap = QPixmap(path);
    }

    void FitImage();
    void SetFolder(const QString& d);
    QString GetCurrentFile();

private slots:
    void on_btn_left_clicked();

    void on_btn_right_clicked();

    void on_action_choose_dir_triggered();

    void on_action_use_resources_triggered();

    void on_act_quit_app_triggered();

    void on_action_up_windows_toggled(bool checked);

    void on_action_0sec_triggered();

    void on_action_1sec_toggled(bool arg1);

    void on_action_5sec_toggled(bool arg1);

    void on_action_10sec_toggled(bool arg1);

    void on_timeout();

private:
    void resizeEvent(QResizeEvent *event) override;
    void UpdateEnabled();
    void UpdateInterval(int interval);
    prac::QTimer timer{this};
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QLabel lbl_new_{this};
    QString current_folder_;
    int cur_file_index_ = 0;
    int slideshow_interval_;
    bool is_interval_updating_ = false;
};
#endif // MAINWINDOW_H
