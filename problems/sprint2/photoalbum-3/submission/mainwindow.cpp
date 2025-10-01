#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    Q_ASSERT(!active_pixmap.isNull());

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
    QStringList list_files = dir.entryList();
    int total = int(list_files.size());
    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);
    return dir.filePath(list_files[file_index]);
}



void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}

void MainWindow::UpdateEnabled()
{
    int amount_of_images = QDir(current_folder_).entryList().size();
    ui->btn_left->setEnabled(cur_file_index_ > 0);
    ui->btn_right->setEnabled(cur_file_index_ < amount_of_images - 1);
}

void MainWindow::on_btn_left_clicked()
{
    cur_file_index_ -= 1;
    UpdateEnabled();
    SetPixmap(GetCurrentFile());
    FitImage();
}


void MainWindow::on_btn_right_clicked()
{
    cur_file_index_ += 1;
    UpdateEnabled();
    SetPixmap(GetCurrentFile());
    FitImage();
}

