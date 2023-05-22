#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <approximation.h>
#include <QVector>

using namespace std;

class Interpolation : public Approximation
{
protected:
    //Поле для точек на оси абцисс
    QVector<double> x;
    //Поле для точек на оси ординат
    QVector<double> y;

public:
    Interpolation(const QVector<double> x_input, const QVector<double> y_input) : x(x_input), y(y_input){}
    ~Interpolation() {}
    virtual double calc(const double x_value) = 0;
};

class Linear_Interpolation : public Interpolation
{
public:
    Linear_Interpolation(const QVector<double> x_input, const QVector<double> y_input) : Interpolation(x_input, y_input){}
    ~Linear_Interpolation() {}
    double calc(const double x_value);
};

class Quadratic_Interpolation : public Interpolation
{
public:
    Quadratic_Interpolation(const QVector<double> x_input, const QVector<double> y_input) : Interpolation(x_input, y_input){}
    ~Quadratic_Interpolation() {}
    double calc(const double x_value);
};

class Lagranzh_polinom : public Interpolation
{
public:
    Lagranzh_polinom(const QVector<double> x_input, const QVector<double> y_input) : Interpolation(x_input, y_input){}
    ~Lagranzh_polinom() {}
    double calc(const double x_value);
};

class Newton_polinom : public Interpolation
{
public:
    Newton_polinom(const QVector<double> x_input, const QVector<double> y_input) : Interpolation(x_input, y_input){}
    ~Newton_polinom() {}
    double calc(const double x_value);
};

#endif // INTERPOLATION_H
