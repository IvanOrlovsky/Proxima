#ifndef REGRESSION_H
#define REGRESSION_H

#include<approximation.h>
#include <QVector>

using namespace std;

class Regression : public Approximation
{
protected:
    //Вектор точек оси абцисс
    QVector<double> x;
    //Вектор точек оси ординат
    QVector<double> y;
    //Коэффициенты для разных видов регрессии
    double a, b, c;
public:
    Regression(const QVector<double> x_input, const QVector<double> y_input) :  x(x_input), y(y_input), a(0.0), b(0.0), c(0.0) {}
    ~Regression() {}
    virtual double calc(const double x_value) = 0;
};

class Linear_Regression : public Regression
{
public:

    Linear_Regression(const QVector<double> x_input, const QVector<double> y_input) : Regression(x_input, y_input){}
    ~Linear_Regression() {}

    double calc(const double x_value);
};

class Hyperbolic_Regression : public Regression
{
public:

    Hyperbolic_Regression(const QVector<double> x_input, const QVector<double> y_input) : Regression(x_input, y_input){}
    ~Hyperbolic_Regression() {}

    double calc(const double x_value);
};

class Quadratic_Regression : public Regression
{

public:
    Quadratic_Regression(const QVector<double> x_input, const QVector<double> y_input) : Regression(x_input, y_input){}
    ~Quadratic_Regression() {}

    double calc(const double x_value);
};


class Exponential_Regression : public Regression
{
  public:

  Exponential_Regression(const QVector<double> x_input, const QVector<double> y_input) : Regression(x_input, y_input){}
  ~Exponential_Regression() {}

  double calc(const double x_value);
};


#endif // REGRESSION_H
