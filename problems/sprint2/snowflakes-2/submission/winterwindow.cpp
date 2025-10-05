#include "winterwindow.h"
#include "ui_winterwindow.h"
#include <QColorDialog>
#include <QPaintEvent>

WinterWindow::WinterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WinterWindow)
{
    ui->setupUi(this);
}

WinterWindow::~WinterWindow()
{
    delete ui;
}

void WinterWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    prac::QPainter painter(this);
    double size = double(ui->sld_size->value());

    double scale_factor = 0.0;
    if (ui->sld_factor->maximum() != 0) {
        scale_factor = ui->sld_factor->value() / (double)ui->sld_factor->maximum();
    }

    SnowFlakeParams flake_params{
        .center = {width() / 2., height() / 2.},
        .color = color_,
        .size = size,
        .line_width = ui->sld_line->value() / 15.0,
        .rotation = double(ui->sld_rotation->value()),
        .depth = ui->spin_depth->value(),
        .scale_factor = scale_factor
    };

    SnowFlake snowflake(flake_params);
    snowflake.Draw(painter);


    QRect rect(10, 10, width() - 20, height() - 20);

    QFont font("Verdana", 12);
    painter.setFont(font);
    painter.setPen(Qt::white);

    painter.drawText(rect, Qt::AlignTop | Qt::AlignLeft, snowflake.GetDescription());
}

void WinterWindow::on_btn_color_clicked()
{
    QColorDialog dialog{color_};
    dialog.exec();
    color_ = dialog.selectedColor();
    update();
}
