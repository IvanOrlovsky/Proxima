#ifndef APPROXIMATION_H
#define APPROXIMATION_H

class Approximation
{
public:
    Approximation() {}
    //метод подсчета значений функции аппроксимации
    virtual double calc(const double x_value) = 0;
};

#endif // APPROXIMATION_H
