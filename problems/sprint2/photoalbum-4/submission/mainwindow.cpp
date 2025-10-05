#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileInfo>


[[nodiscard]] QPixmap ResizeImgToFit(
    const QPixmap &src,
    int window_width,
    int window_height
) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;

    if ( w_ratio < h_ratio ) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    ui->action_up_windows->setChecked(true);
    SetFolder(":/cats/images/");
    FitImage();
    UpdateEnabled();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    if (active_pixmap.isNull()) {
        lbl_new_.clear();
        return;
    }

    QPixmap scaled_pixmap = ResizeImgToFit(active_pixmap, width(), height());
    lbl_new_.setPixmap(scaled_pixmap);
    lbl_new_.resize(scaled_pixmap.size());

    int lbl_x = (width() - scaled_pixmap.width()) / 2;
    int lbl_y = (height() - scaled_pixmap.height()) / 2;

    lbl_new_.move(lbl_x, lbl_y);
}

void MainWindow::SetFolder(const QString &d)
{
    current_folder_ = d;
    cur_file_index_ = 0;
    SetPixmap(GetCurrentFile());
}

QString MainWindow::GetCurrentFile()
{
    QDir dir(current_folder_);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.jxr";
    QStringList list_files = dir.entryList(nameFilters, QDir::Files | QDir::Readable);

    if (list_files.isEmpty()) {
        return QString();
    }

    int total = int(list_files.size());
    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);
    cur_file_index_ = file_index;
    return dir.filePath(list_files[file_index]);
}



void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}

void MainWindow::UpdateEnabled()
{
    QDir dir(current_folder_);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.jxr";
    int amount_of_images = dir.entryList(nameFilters, QDir::Files | QDir::Readable).size();
    ui->btn_left->setEnabled(cur_file_index_ > 0);
    ui->btn_right->setEnabled(cur_file_index_ < amount_of_images - 1);
}

void MainWindow::on_btn_left_clicked()
{
    cur_file_index_ -= 1;
    SetPixmap(GetCurrentFile());
    FitImage();
    UpdateEnabled();
}


void MainWindow::on_btn_right_clicked()
{
    cur_file_index_ += 1;
    SetPixmap(GetCurrentFile());
    FitImage();
    UpdateEnabled();
}


void MainWindow::on_action_choose_dir_triggered()
{
    QString filePath = prac::QFileDialog::getExistingDirectory(this,
                                                         QString("Open Folder"),
                                                         QString(current_folder_),
                                                         prac::QFileDialog::DontResolveSymlinks);

    if (filePath.isEmpty()) { return; }

    QDir dir(filePath);
    QStringList nameFilters;
    nameFilters << "*.jpg" << "*.jpeg" << "*.png" << "*.jxr";
    if (dir.entryList(nameFilters, QDir::Files | QDir::Readable).isEmpty()) {
        current_folder_ = filePath;
        cur_file_index_ = 0;
        active_pixmap = QPixmap();
        FitImage();
        UpdateEnabled();
        return;
    }

    SetFolder(filePath);
    FitImage();
    UpdateEnabled();
}

void MainWindow::on_action_use_resources_triggered()
{
    QString file = prac::QFileDialog::getOpenFileName(this,
                                                QString("Pick File"),
                                                QString(current_folder_),
                                                "*.jpg;*.jpeg;*.png;*.jxr;");

    if (file.isEmpty()) { return; }

    SetPixmap(file);
    FitImage();

    ui->btn_left->setEnabled(false);
    ui->btn_right->setEnabled(false);
}

void MainWindow::on_act_quit_app_triggered()
{
    close();
}

void MainWindow::on_action_up_windows_toggled(bool checked)
{
    if (checked) {
        setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        setWindowFlags(windowFlags() & ~Qt::WindowStaysOnTopHint);
    }
    show();
}
