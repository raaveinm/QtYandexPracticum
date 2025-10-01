#include "mywindowwithimage.h"
#include "ui_mywindowwithimage.h"

#include <QFileInfo>
#include <QDir>

#include <QtGlobal>

#define MACRO_TO_STR_INNER(x) #x
#define MACRO_TO_STR(x) MACRO_TO_STR_INNER(x)

MyWindowWithImage::MyWindowWithImage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyWindowWithImage)
{
    ui->setupUi(this);

    QString image_path = MACRO_TO_STR(ILOVEQT_IMAGE_FULL_PATH);
    SetPixmap(ui->lbl_pixmap, image_path);
    FitToImage(ui->lbl_pixmap);
}

MyWindowWithImage::~MyWindowWithImage()
{
    delete ui;
}

void MyWindowWithImage::SetPixmap(QLabel *label_pix, const QString path)
{
    QPixmap pix(path);
    Q_ASSERT(!pix.isNull());

    label_pix->setPixmap( pix );
    label_pix->show();
}

void MyWindowWithImage::FitToImage(QLabel *lbl)
{
    int width = lbl->pixmap().width();
    int height = lbl->pixmap().height();
    lbl->move(0,0);
    lbl->setFixedSize(width, height);
    setFixedSize(width, height);
    adjustSize();
}
