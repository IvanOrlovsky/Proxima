#include "interpolation.h"


#include  <iostream>
double Linear_Interpolation :: calc(const double x_value)
{
    double result = 0.0;

    for (int i = 0; i < x.size() - 1; i++)
    {
        // Если точка x_value находится между двумя соседними точками
        if (x_value >= x[i] && x_value <= x[i + 1])
        {
            // Расчет значения коэффициента наклона прямой между двумя точками
            double k = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
            // Расчет значения интерполяции в точке x_value с помощью уравнения прямой
            result = y[i] + (x_value - x[i]) * k;
            break;
        }
    }

    return result; // Возвращаем вычисленное значение
}

double Quadratic_Interpolation :: calc(const double x_value)
{
    double result = 0.0;
    for (int i = 0; i < x.size() - 1; i++)
    {
        //Если точка x_value находится между тремя соседними точками
        if (x_value >= x[i] && x_value <= x[i + 2])
        {
            //если знаменатели не обнуляются
            if( (x[i] - x[i+1]) * (x[i] - x[i+2]) != 0 && (x[i+1] - x[i]) * (x[i+1] - x[i+2]) != 0 && (x[i+2] - x[i]) * (x[i+2] - x[i+1]) != 0)
            {
                result += y[i] * (x_value - x[i+1]) * (x_value - x[i+2]) / ((x[i] - x[i+1]) * (x[i] - x[i+2]));
                result += y[i+1] * (x_value - x[i]) * (x_value - x[i+2]) / ((x[i+1] - x[i]) * (x[i+1] - x[i+2]));
                result += y[i+2] * (x_value - x[i]) * (x_value - x[i+1]) / ((x[i+2] - x[i]) * (x[i+2] - x[i+1]));
            }
            break;
        }
    }

    return result;
}

double Lagranzh_polinom::calc(const double x_value)
{
    double result = 0.0;

    for(int i = 0; i < (int)x.size(); i++)
    {
        //Счет значения базисного полинома Лагранжа
        double l = 1.0;
        for(int j = 0; j < (int)x.size(); j++)
        {
            if(i != j)
            {
                l *= (x_value - x[j]) / (x[i] - x[j]);
            }
        }
        result += y[i] * l;
    }

    return result;
}


double Newton_polinom::calc(const double x_value)
{
//    double result = y[0];
//    double den, F;

//    for(int i = 0; i < (int)x.size(); i++)
//    {
//        F = 0.0;
//        for(int j = 0; j <= i; j++)
//        {
//            den = 1.0;
//            for(int k = 0; k <= i; k++)
//            {
//                if(k != j)
//                {
//                    den *= (x[j] - x[k]);
//                }
//            }
//            F += y[j] / den;
//        }
//        for(int k = 0; k < i; k++)
//        {
//            F *= (x_value - x[k]);
//        }
//        result += F;
//    }
//    return result;


    int n = x.size();
    double result = y[0];  // Начальное значение полинома

    for (int i = 1; i < n; ++i) {
        double term = y[i];

        for (int j = 0; j < i; ++j) {
            term *= (x_value - x[j]);
        }

        result += term;
    }

    return result;
}
