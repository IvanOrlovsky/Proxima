#ifndef RENDER_H
#define RENDER_H

#include <map>
#include <QString>
#include <QGroupBox>
#include <QCheckBox>
#include <QVector>
#include "approximation.h"
#include "regression.h"
#include "interpolation.h"
#include "customplot.h"

class Render
{
private:
    static std::map<QString, Approximation*> mp;

public:
    Render(){}

    //метод получения вектора координат ординат
    static QVector<double> getYvector(const QString chckbx_name, const QVector<double> values);
    //метод получения вектора координат абцисс
    static QVector<double> getXvector(const QString value_input);
    //метод вывода точек
    static void Render_dots( const QVector<double> x,  const QVector<double> y, customPlot &plot);

    //метод получения вектора чисел из строки
    static QVector<double> QVectorfromQString(QString input);
    //метод, выводящий график
    static void Render_graph(const QGroupBox &groupbox, customPlot &plot, const QString x_input);
    //метод, создающий map
    static void createMap(const QString x, const QString y);
    //метод проверки строки на содержание только чисел
    static bool QStringContainsOnlyNums(const QString qstr);
};

#endif // RENDER_H
