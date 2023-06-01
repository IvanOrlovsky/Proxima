#include "customplot.h"

qreal customPlot::maxScale = 1.0;

customPlot::customPlot(QWidget *parent) : QGraphicsView(parent)
{
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
    currentRect.setRect(-this->width() / 2,
                        -this->height() / 2,
                        this->width(),
                        this->height());
    scene->setSceneRect(currentRect);

    //Отрисовка сетки графика
    grid = new QGraphicsItemGroup();

    grid_step = 40;
    gridPaint(QRectF(-this->width() / 2,
                     -this->height() / 2,
                     this->width(),
                     this->height()));

    //Отрисовка осей
    grid_pen.setColor(Qt::black);
    grid_pen.setWidthF(1.4);
    grid->addToGroup(scene->addLine(-16777215, 0, 16777215, 0, grid_pen));
    grid->addToGroup(scene->addLine(0, 16777215, 0, -16777215, grid_pen));

    scene->addItem(grid);
}

customPlot::~customPlot()
{
    delete dots;
    delete plot;
    delete grid;
    delete scene;
}

void customPlot::addPlot(QVector<double> x, QVector<double> y)
{
    // Находим минимальные и максимальные значения координат x и y
    double minX = *x.begin() * grid_step;
    double maxX = *(x.end() - 1) * grid_step;
    double minY = *(std::min_element(y.begin(), y.end())) * grid_step;
    double maxY = *(std::max_element(y.begin(), y.end())) * grid_step;

    QRect plotRect(minX,
                   -maxY,
                   maxX - minX,
                   maxY - minY);

    currentRect.setRect(plotRect.center().x() - this->width()/2,
                        plotRect.center().y() - this->height()/2,
                        this->width(),
                        this->height());

    if(qMax(currentRect.width(), currentRect.height()) < qMax(plotRect.width(), plotRect.height()))
    {
        currentRect.setRect(plotRect.center().x() - qMax(plotRect.width(), plotRect.height())/2 - grid_step,
                            plotRect.center().y() - qMax(plotRect.width(), plotRect.height())/2 - grid_step,
                            qMax(plotRect.width(), plotRect.height()) + 2 * grid_step,
                            qMax(plotRect.width(), plotRect.height()) + 2 * grid_step);
    }

    scene->setSceneRect(currentRect);

    maxScale = (currentRect.width() * currentRect.height())/(plotRect.width() * plotRect.height()) / grid_step;

    // Очищаем предыдущий график, если есть
    if (plot != nullptr)
    {
        scene->removeItem(plot);
        delete plot;
    }

    // Создаем новый QGraphicsItemGroup для графика
    plot = new QGraphicsItemGroup();

    // Отрисовываем точки графика
    for (int i = 0; i < x.size() - 1; i++)
    {
        plot->addToGroup(scene->addLine(QLineF(x[i] * grid_step, -y[i] * grid_step, x[i + 1] * grid_step, -y[i + 1] * grid_step),
                                        QPen(QColor(250, 1, 1), 4)));
    }

    // Добавляем график на сцену
    scene->addItem(plot);

    gridPaint(currentRect);
}


void customPlot::addPoints(QVector<double> x, QVector<double> y)
{
    if(dots != nullptr)
        scene->removeItem(dots);
    dots = new QGraphicsItemGroup();
    for(int i = 0; i < x.size(); i++)
    {
        dots->addToGroup(scene->addEllipse(x[i] * grid_step - 2.5,
                                           -y[i] * grid_step - 2.5,
                                           5,
                                           5,
                                           QPen(QColor(66, 243, 252)),
                                           QBrush(QColor(66, 243, 252))));
    }
    scene->addItem(dots);
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

        // Получаем текущий масштаб
        qreal currentScale = this->transform().m11();

        // Масштабируем смещение мыши в зависимости от текущего масштаба
        delta /= currentScale;

        QPointF newCenter(currentCenter.x() - delta.x(),
                          currentCenter.y() - delta.y());

        this->centerOn(newCenter);

        curruntMousePos = event->pos();
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

void customPlot::gridPaint(const QRectF& currRect)
{
    for (auto i : verticalGrid)
    {
        scene->removeItem(i);
        delete i;
    }
    for (auto i : gorizontalGrid)
    {
        scene->removeItem(i);
        delete i;
    }
    verticalGrid.clear();
    gorizontalGrid.clear();

    grid_pen.setWidthF(0.3);
    grid_pen.setColor(Qt::lightGray);

    for (qreal i = currRect.left() - 400.0; i < (currRect.right() + 400.0); i += 1.0)
    {
        if (std::fmod(i, (double)grid_step) == 0.0)
        {
            verticalGrid.push_back(new QGraphicsItemGroup());
            verticalGrid[verticalGrid.size() - 1]->addToGroup(scene->addLine(i,
                                                                             currentRect.top() - grid_step - 400.0,
                                                                             i,
                                                                             currentRect.bottom() + grid_step + 400.0,
                                                                             grid_pen));
        }
    }

    for (auto i : verticalGrid)
    {
        scene->addItem(i);
    }

    for (qreal i = currRect.top() - 400.0; i < (currRect.bottom() + 400.0); i += 1.0)
    {
        if (std::fmod(i, (double)grid_step) == 0.0)
        {
            gorizontalGrid.push_back(new QGraphicsItemGroup());
            gorizontalGrid[gorizontalGrid.size() - 1]->addToGroup(scene->addLine(currentRect.left() - grid_step - 400.0,
                                                                                 i,
                                                                                 currentRect.right() + grid_step + 400.0,
                                                                                 i,
                                                                                 grid_pen));
        }
    }

    for (auto i : gorizontalGrid)
    {
        scene->addItem(i);
    }
}



void customPlot::wheelEvent(QWheelEvent *event)
{
    // Получаем угол поворота колеса мыши
    int delta = event->angleDelta().y();

    // Определяем коэффициент масштабирования
    double scaleFactor = 1.15;
    qDebug() << this->transform().m11() << "\n";
    qDebug() << maxScale << "\n";
    if (delta > 0)
    {
        // Увеличиваем масштаб
        this->scale(scaleFactor, scaleFactor);
    }
    else if(qMax(this->width(), this->height()) < qMax(currentRect.width(), currentRect.height()) * this->transform().m11())
    {
        // Уменьшаем масштаб
        this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void customPlot::getPNG()
{
    // Создаем QPixmap и устанавливаем его размер равным размеру сцены
    QPixmap pixmap(this->viewport()->size());
    pixmap.fill(Qt::transparent); // Заполняем QPixmap прозрачным цветом

    // Создаем QPainter для рисования на QPixmap
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    // Рисуем сцену на QPixmap с использованием QGraphicsView
    this->render(&painter);

    // Завершаем рисование
    painter.end();

    // Запрос пользователю сохранить файл PNG
    QString filePath = QFileDialog::getSaveFileName(this->parentWidget(), "Сохранить PNG", QString(), "PNG (*.png)");

    if (!filePath.isEmpty()) {
        // Сохранение pixmap в файл PNG
        pixmap.save(filePath);
    }
}
