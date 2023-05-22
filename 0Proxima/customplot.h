#ifndef CUSTOMPLOT_H
#define CUSTOMPLOT_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QMouseEvent>
#include <QScrollEvent>
#include <QTransform>
#include <QVector>
#include <QGraphicsSimpleTextItem>

class customPlot : public QGraphicsView
{
    Q_OBJECT

public:
    customPlot(QWidget *parent = 0);
    ~customPlot();
    //Метод возвращения в начало координат
    void returnToCenter();
    //Метод добавления графика
    void addPlot(QVector<double> x, QVector<double> y);
    //Метод добавления точек
    void addPoints(QVector<double> x, QVector<double> y);
public slots:

signals:

private slots:

private:
    QVector<QGraphicsItemGroup*> verticalGrid;
    QVector<QGraphicsItemGroup*> gorizontalGrid;
    //скорости увеличения и уменьшения шасштаба
    const qreal SCALE_INCREMENT = 0.2;
    const qreal SCALE_DECREMENT = 0.2;
    //скорости передвижения по плоскости по осям
    qreal MOVE_SPEED_X = 100.0;
    qreal MOVE_SPEED_Y = 100.0;
    //Константы минимума и максимума скоростей переджижения
    const qreal MAX_MOVE_SPEED_X = 200;
    const qreal MAX_MOVE_SPEED_Y = 200;
    const qreal MIN_MOVE_SPEED_X = 100;
    const qreal MIN_MOVE_SPEED_Y = 100;
    //Переопределение методов для перемещения по плоскости
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //
    void gridPaint(QRectF *currRect);
    //Переопределение методa прокрутки колеса мыши для масштабирования
    void wheelEvent(QWheelEvent *event) override;
    //Координаты мыши в момент удержания графика
    QPoint curruntMousePos;
    //Переменная для проверки нажатия мыши
    bool isMousePressed;
    //сцена для отрисовки координатной плоскости
    QGraphicsScene *scene;
    //Сама сетка
    QGraphicsItemGroup *grid;
    //Шаг сетки графикa
    int grid_step;
    //Ручка для отрисовки сетки
    QPen grid_pen;
    //график
    QGraphicsItemGroup *plot;
    //точки
    QGraphicsItemGroup *dots;
    //цифры
    QVector<QGraphicsSimpleTextItem*> numbers;
};

#endif // CUSTOMPLOT_H
