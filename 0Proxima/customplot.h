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
#include <QDebug>
#include <QScrollBar>

class customPlot : public QGraphicsView
{
    Q_OBJECT

public:
    customPlot(QWidget *parent = 0);
    ~customPlot();
    //Метод добавления графика
    void addPlot(QVector<double> x, QVector<double> y);
    //Метод добавления точек
    void addPoints(QVector<double> x, QVector<double> y);
public slots:

signals:

private slots:

private:
    static qreal maxScale;
    QVector<QGraphicsItemGroup*> verticalGrid;
    QVector<QGraphicsItemGroup*> gorizontalGrid;
    QRectF currentRect;
    //Переопределение методов для перемещения по плоскости
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //
    void gridPaint(const QRectF& currRect);
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
