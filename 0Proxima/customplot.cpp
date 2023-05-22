#include "customplot.h"

#include <QDebug>
#include <QScrollBar>

customPlot::customPlot(QWidget *parent) : QGraphicsView(parent)
{
    MOVE_SPEED_X = 100.0;
    MOVE_SPEED_Y = 100.0;
    plot = nullptr;
    scene = nullptr;
    grid = nullptr;
    dots = nullptr;

    //Настройка отображения виджета
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setBaseSize(960 - 343, 540);

    //Создание сцены
    scene = new QGraphicsScene();
    this->setScene(scene);
    scene->setSceneRect(-this->width() / 2, -this->height() / 2, this->width(), this->height());

    //Отрисовка сетки графика
    grid = new QGraphicsItemGroup();
    //Отрисовка сетки и чисел
    grid_step = 50;
    grid_pen.setWidthF(0.3);
    grid_pen.setColor(Qt::lightGray);


//    //Вертикальные линии
//    for(int i = 0, j = 0; i > -(int)this->width() - grid_step; i -= grid_step, j++)
//    {
//        verticalGrid.push_back(new QGraphicsItemGroup());
//        verticalGrid[j]->addToGroup(scene->addLine(i, this->height() + grid_step, i, -this->height() - grid_step, grid_pen));
//    }
//    for(int i = 0, j = 0; i < (int)this->width() + grid_step; i += grid_step, j++)
//    {
//        verticalGrid.push_back(new QGraphicsItemGroup());
//        verticalGrid[j]->addToGroup(scene->addLine(i, this->height() + grid_step, i, -this->height() - grid_step, grid_pen));
//    }

//    //Горизонтальные линии
//    for(int i = 0, j = 0; i > -(int)this->height() - grid_step; i -= grid_step, j++)
//    {
//        gorizontalGrid.push_back(new QGraphicsItemGroup());
//        gorizontalGrid[j]->addToGroup(scene->addLine(this->width() + grid_step, i, -this->width() - grid_step, i, grid_pen));
//    }
//    for(int i = 0, j = 0; i < (int)this->height() + grid_step; i += grid_step, j++)
//    {
//        gorizontalGrid.push_back(new QGraphicsItemGroup());
//        gorizontalGrid[j]->addToGroup(scene->addLine(this->width() + grid_step, i, -this->width() - grid_step, i, grid_pen));
//    }
//    for(int i = 0, j = 0; i < (int)this->height() + grid_step; i += grid_step, j -= grid_step)
//    {

 //   }

    //Отрисовка осей
    grid_pen.setColor(Qt::black);
    grid_pen.setWidthF(1.2);
    grid->addToGroup(scene->addLine(-16777215, 0, 16777215, 0, grid_pen));
    grid->addToGroup(scene->addLine(0, 16777215, 0, -16777215, grid_pen));

//    for(auto i : verticalGrid)
//    {
//        scene->addItem(i);
//    }
//    for(auto i : gorizontalGrid)
//    {
//        scene->addItem(i);
//    }

    scene->addItem(grid);

    //ставим поле зрения в центр
    returnToCenter();
}

customPlot::~customPlot()
{
    delete dots;
    delete plot;
    delete grid;
    delete scene;
}

void customPlot::returnToCenter()
{
    QTransform center;
    center.translate(this->width() / 4, this->height() / 4);
    center.scale(1, 1);

    this->setTransform(center);
}

void customPlot::addPlot(QVector<double> x, QVector<double> y)
{
    // Находим минимальные и максимальные значения координат x и y
    double minX = *x.begin() * grid_step;
    double maxX = *(x.end() - 1) * grid_step;
    double minY = *(std::min_element(y.begin(), y.end())) * grid_step;
    double maxY = *(std::max_element(y.begin(), y.end())) * grid_step;

    QRect plotRect(minX, -maxY, maxX - minX, maxY - minY);
    scene->setSceneRect(plotRect.center().x() - this->width()/2, plotRect.center().y() - this->height()/2, this->width(), this->height());
    this->centerOn(QRectF(plotRect.center().x() - this->width()/2, plotRect.center().y() - this->height()/2, this->width(), this->height()).center());

    // Очищаем предыдущий график, если есть
    if (plot != nullptr) {
        scene->removeItem(plot);
        delete plot;
    }

    // Создаем новый QGraphicsItemGroup для графика
    plot = new QGraphicsItemGroup();

    // Отрисовываем точки графика
    for (int i = 0; i < x.size(); i++) {
        plot->addToGroup(scene->addEllipse(x[i] * grid_step, -y[i] * grid_step, 2, 2, QPen(QColor(250, 1, 1), 2)));
    }

    // Добавляем график на сцену
    scene->addItem(plot);
}

void customPlot::addPoints(QVector<double> x, QVector<double> y)
{
    if(dots != nullptr)
        scene->removeItem(dots);
    dots = new QGraphicsItemGroup();
    for(int i = 0; i < x.size(); i++)
    {
        dots->addToGroup(scene->addEllipse(x[i] * grid_step, -y[i] * grid_step, 5, 5, QPen(QColor(1,1,250)), QBrush(Qt::blue)));
    }
    scene->addItem(dots);
    returnToCenter();
}

void customPlot::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        isMousePressed = true;
        curruntMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }

}



void customPlot::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
    if(isMousePressed)
    {
        QPoint delta = event->pos() - curruntMousePos;
        QPointF currentCenter = this->mapToScene(this->viewport()->rect().center());

        // Move the center point by the mouse delta
        QPointF newCenter(currentCenter.x() - delta.x(), currentCenter.y() - delta.y());

        // Set the new center point of the scene
        this->centerOn(newCenter);

        // Update the last mouse position
        curruntMousePos = event->pos();

        // Update the view
        this->update();
    }
}



void customPlot::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if (event->button() == Qt::LeftButton)
    {
        isMousePressed = false;
        setCursor(Qt::ArrowCursor);
    }
}

void customPlot::gridPaint(QRectF *currRect)
{
    for(qreal i = currRect->left() - 100.0; i < (currRect->right() + 100.0); i += 1.0)
    {
        verticalGrid.push_back(new QGraphicsItemGroup());
        verticalGrid[j]->addToGroup(scene->addLine(i, this->height() + grid_step, i, -this->height() - grid_step, grid_pen));
    }
}

void customPlot::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
    QTransform scale = this->transform();
    if(event->angleDelta().y() > 0)
    {
        scale.setMatrix(scale.m11()+ SCALE_INCREMENT, scale.m12(), scale.m13(),
                        scale.m21(), scale.m22() + SCALE_INCREMENT, scale.m23(),
                        scale.m31(), scale.m32(), scale.m33() );
        this->setTransform(scale);
    }
    else
    {
        scale.setMatrix(scale.m11()- SCALE_DECREMENT, scale.m12(), scale.m13(),
                        scale.m21(), scale.m22() - SCALE_DECREMENT, scale.m23(),
                        scale.m31(), scale.m32(), scale.m33() );
        this->setTransform(scale);
    }
}


