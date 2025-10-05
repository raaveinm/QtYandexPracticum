#ifndef WINTERWINDOW_H
#define WINTERWINDOW_H

#include <QMainWindow>
#include <prac/QPainter>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui {
class WinterWindow;
}
QT_END_NAMESPACE

struct Vector2D {
    double x;
    double y;
};

struct Point2D {
    double x;
    double y;
};

inline Vector2D RotateVector(Vector2D src, double angle) {
    double a_rad = angle / 180. * M_PI;
    double sin_v = std::sin(a_rad);
    double cos_v = std::cos(a_rad);
    return Vector2D{
        src.x * cos_v + src.y * sin_v, - src.x * sin_v + src.y * cos_v
    };
}

inline Vector2D Add(Vector2D l, Vector2D r) {
    return Vector2D{l.x + r.x, l.y + r.y};
}

inline Point2D Add(Point2D l, Vector2D r) {
    return Point2D{l.x + r.x, l.y + r.y};
}

struct SnowFlakeParams {
    Point2D center;
    QColor color;
    double size;
    double line_width;
    double rotation;
    int depth;
    double scale_factor;
};

class SnowFlake {
public:
    SnowFlake(SnowFlakeParams params) : params_(params) {}

    void Draw(prac::QPainter& painter) const {
        QPen pen(params_.color);
        pen.setWidthF(params_.line_width);
        painter.setPen(pen);
        for (int i = 0; i < 6; ++i) {

            double current_ray_angle = params_.rotation + i * 60;
            Point2D end_point = DrawRotatedVector(painter, params_.center, current_ray_angle, params_.size);

            if (params_.depth > 0) {

                SnowFlake next_flake = GetNextLevelFlake(end_point, current_ray_angle);
                next_flake.Draw(painter);
            }
        }
    }

    QString GetDescription() const {
        return QString("Размер %1\nТолщина линии %2\nПоворот %3\nМножитель %4")
            .arg(params_.size)
            .arg(params_.line_width)
            .arg(params_.rotation)
            .arg(params_.scale_factor);
    }

private:
    SnowFlake GetNextLevelFlake(Point2D center, double parent_ray_angle) const {
        SnowFlakeParams next_params = params_;
        next_params.center = center;
        next_params.size *= params_.scale_factor;
        next_params.depth -= 1;
        return SnowFlake(next_params);
    }

    static Point2D DrawRotatedVector(prac::QPainter& painter, Point2D center, double angle, double length) {
        Vector2D rotated_vector = RotateVector(Vector2D{length, 0}, angle);
        Point2D end_point = Add(center, rotated_vector);
        painter.drawLine(QPointF{center.x, center.y}, QPointF{end_point.x, end_point.y});
        return end_point;
    }

private:
    SnowFlakeParams params_;
};

class WinterWindow : public QMainWindow
{
    Q_OBJECT

public:
    WinterWindow(QWidget *parent = nullptr);
    ~WinterWindow();

private slots:
    void on_btn_color_clicked();

private:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::WinterWindow *ui;
    QColor color_ = Qt::white;
};
#endif // WINTERWINDOW_H
