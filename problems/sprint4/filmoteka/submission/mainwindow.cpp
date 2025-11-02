#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_pb_add_clicked() {
    if (ui->le_name->text().isEmpty()) { return; }

    const Movie movie = GetMovie();

    if (movies_.indexOf(movie) == -1) {
        movies_.append(movie);
    } else {
        movies_[movies_.indexOf(movie)] = movie;
    }

    ApplyModel(movie);
}

void MainWindow::ApplyModel(const Movie &selection) {
    ui->cb_list_done->blockSignals(true);
    ui->cb_list_wait->blockSignals(true);


    int index_d = ui->cb_list_done->currentIndex();
    int index_w = ui->cb_list_wait->currentIndex();

    ui->cb_list_done->clear();
    ui->cb_list_wait->clear();

    for (const Movie& movie : movies_) {
        if (movie.is_watched) {
            ui->cb_list_done->addItem(ToString(movie));
            ui->cb_list_done->setCurrentIndex(ui->cb_list_done->findText(ToString(selection)));
        } else {
            ui->cb_list_wait->addItem(ToString(movie));
            ui->cb_list_wait->setCurrentIndex(ui->cb_list_wait->findText(ToString(selection)));
        }
    }

    selection.is_watched ? ui->cb_list_done->setCurrentIndex(index_d) : ui->cb_list_wait->setCurrentIndex(index_w);

    ui->cb_list_done->blockSignals(false);
    ui->cb_list_wait->blockSignals(false);

    // Заполните виджеты ui->cb_list_done и ui->cb_list_wait,
    // используя их методы clear и addItems.
    // Вам пригодится метод ToString.
    // Также примените выделение, используя метод
    // setCurrentIndex.
}

QString MainWindow::ToString(const Movie &movie) {
    QString str_genre = "";
    switch(movie.genre) {
    case Genre::kComedy : str_genre = "Комедия"; break;
    case Genre::kAction : str_genre = "Боевик"; break;
    case Genre::kDrama : str_genre = "Драма"; break;
    case Genre::kFairyTale : str_genre = "Сказка"; break;
    case Genre::kAnimation : str_genre = "Мультфильм"; break;
    case Genre::kHorror : str_genre = "Ужасы"; break;
    }
    return str_genre + " '" + movie.name + "' рейтинг: " + QString::number(movie.rating);
}

QStringList MainWindow::ToString(const QList<Movie> &movies) {
    QStringList result;
    for (const Movie& movie : movies) {
        if (movie.name.isEmpty()){ continue; }
        result.append(ToString(movie));
    }
    return result;
}

Movie MainWindow::GetMovie() const {
  return Movie{.name = ui->le_name->text(),
    .genre = static_cast<Genre>(ui->cb_genre->currentIndex()),
    .rating = ui->dsb_rating->value(),
    .is_watched = ui->chb_is_done->isChecked()};
}

void MainWindow::ApplyMovie(const Movie &movie) const {
    ui->le_name->setText(movie.name);
    ui->cb_genre->setCurrentIndex(static_cast<int>(movie.genre));
    ui->dsb_rating->setValue(movie.rating);
    ui->chb_is_done->setCheckState(movie.is_watched ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
}

void MainWindow::on_cb_list_wait_currentIndexChanged(int index) {
    if (index < 0)
        return;

    QList<Movie> tmp;
    for (const Movie& movie : movies_) {
        if (!movie.is_watched) {
            tmp.append(movie);
        }
    }
    ApplyMovie(tmp[index]);
}

void MainWindow::on_cb_list_done_currentIndexChanged(int index) {
    if (index < 0)
        return;

    QList<Movie> tmp;
    for (const Movie& movie : movies_) {
        if (movie.is_watched) {
            tmp.append(movie);
        }
    }
    ApplyMovie(tmp[index]);
}
