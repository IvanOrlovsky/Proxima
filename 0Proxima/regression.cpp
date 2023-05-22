#include "regression.h"

#include <vector>
#include <string>
#include <math.h>
#include "matrix.h"

double Linear_Regression :: calc(const double x_value)
{
    //переменные для вспомогательных подсчетов
    double
    x_sum = 0.0, //сумма всех x[i]
    y_sum = 0.0, //сумма всех y[i]
    xy_sum = 0.0, //сумма всех x[i] * y[i]
    x2_sum = 0.0; //сумма всех x[i] ^ 2

    for(int i = 0; i < (int)y.size(); ++i)
    {
        x_sum += x[i];
        y_sum += y[i];
        xy_sum += x[i] * y[i];
        x2_sum += x[i] * x[i];
    }

    a = (x_sum * y_sum - (double)y.size() * xy_sum) / (x_sum * x_sum - (double)y.size() * x2_sum);
    b = (x_sum * xy_sum - y_sum * x2_sum) / (x_sum * x_sum - (double)y.size() * x2_sum);

    return a * x_value + b;
}


double Hyperbolic_Regression :: calc(const double x_value)
{
    //переменные для вспомогательных подсчетов
    double
    x_sum = 0.0, //сумма всех 1 / x[i]
    y_sum = 0.0, //сумма всех y[i]
    xy_sum = 0.0, //сумма всех y[i] / x[i]
    x2_sum = 0.0; //сумма всех 1 / (x[i] ^ 2)

    for(int i = 0; i < (int)y.size(); ++i)
    {
        x_sum += 1 / x[i];
        y_sum += y[i];
        xy_sum += y[i] / x[i];
        x2_sum += 1 / (x[i] * x[i]);
    }

    b = ((double)y.size() * xy_sum - x_sum * y_sum) / ((double)y.size() * x2_sum - x_sum * x_sum);
    a = (1 / (double)y.size()) * y_sum - (b / (double)y.size()) * x_sum;

    return a + b / x_value;
}


//TO DO
//Переписать метод
double Quadratic_Regression :: calc(const double x_value)
{
    double
    x_sum = 0.0, //сумма всех x[i]
    x2_sum = 0.0, //сумма всех x[i] ^ 2
    x3_sum = 0.0, //сумма всех x[i] ^ 3
    x4_sum = 0.0, //сумма всех x[i] ^ 4
    y_sum = 0.0, //сумма всех y[i]
    xy_sum = 0.0, //сумма всех x[i] * y[i]
    x2y_sum = 0.0; //сумма всех x[i] ^ 2 * y[i]

    for(int i = 0; i < (int)y.size(); ++i)
    {
        x_sum += x[i];
        x2_sum += x[i] * x[i];
        x3_sum += x[i] * x[i] *x[i];
        x4_sum += x[i] * x[i] * x[i] *x[i];
        y_sum += y[i];
        xy_sum += x[i] * y[i];
        x2y_sum += x[i] * x[i] * y[i];
    }

    QVector<double> coef;
    coef.push_back(x2_sum);
    coef.push_back(x_sum);
    coef.push_back((double)y.size());
    coef.push_back(x3_sum);
    coef.push_back(x2_sum);
    coef.push_back(x_sum);
    coef.push_back(x4_sum);
    coef.push_back(x3_sum);
    coef.push_back(x2_sum);

    QVector<double> free_coef;
    free_coef.push_back(y_sum);
    free_coef.push_back(xy_sum);
    free_coef.push_back(x2y_sum);

    QVector<QVector<double>> slau_coef((int)y.size() , QVector<double>((int)y.size()));
    int k = 0;
    for(int i = 0; i < (int)y.size(); i++)
    {
        for(int j = 0; j < (int)y.size(); j++)
        {
            slau_coef[i][j] = coef[k];
            k++;
        }
    }

    Matrix<double> main_matrix(3, 3, slau_coef);
    Matrix<double> a_matrix(main_matrix), b_matrix(main_matrix), c_matrix(main_matrix);
    a_matrix.replace_column(0, free_coef);
    b_matrix.replace_column(1, free_coef);
    c_matrix.replace_column(2, free_coef);

    double
    main_det = main_matrix.Gauss_method(),
    a_det = a_matrix.Gauss_method(),
    b_det = b_matrix.Gauss_method(),
    c_det = c_matrix.Gauss_method();

    a = a_det / main_det;
    b = b_det / main_det;
    c = c_det / main_det;

    return a * x_value * x_value + b * x_value + c;
}

double Exponential_Regression :: calc(const double x_value)
{
    //переменные для вспомогательных
    //подсчетов
    double
    x_sum = 0.0, //сумма всех x[i]
    x2_sum = 0.0, //сумма всех x[i] ^ 2
    lny_sum = 0.0,//сумма всех ln(y[i])
    xlny_sum = 0.0; //сумма всех x[i] * ln(y[i])

    for(int i = 0; i < (int)y.size(); ++i)
    {
        x_sum += x[i];
        x2_sum += x[i] * x[i];
        lny_sum += log(y[i]);
        xlny_sum += x[i] * log(y[i]);
    }

    b = ((double)y.size() * xlny_sum - x_sum * lny_sum) / ((double)y.size() * x2_sum - x_sum * x_sum);
    a = (1 / (double)y.size()) * lny_sum - (b / (double)y.size()) * x_sum;

    return exp(a + b * x_value);
}
