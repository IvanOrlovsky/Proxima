#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>

using namespace std;

template < typename T >
class Matrix
{
private:
    QVector < QVector < T >> matrix;
    int rows, columns;
    bool det_sign;

public:
    Matrix(): rows(0), columns(0), det_sign(true) {}
    Matrix(const int r, const int c, const QVector < QVector < T >> input);
    Matrix(const Matrix & ref_matrix);
    ~Matrix() {}

    //заменить столбец на произвольный
    void replace_column(const int column, const QVector<T> from);
    //поменять местами столбцы
    void swap_columns(const int from, const int to);
    //поменять местами ряды
    void swap_rows(const int from, const int to);
    //приведение к ступенчатому виду
    void strairs();
    //Вычисление определителя методом Гаусса
    T Gauss_method();
};

template < typename T >
Matrix < T > :: Matrix(const int r, const int c, const QVector < QVector < T >> input)
{
    rows = r;
    columns = c;
    det_sign = true;
    //matrix.resize(r, QVector < T > (c));
    matrix.resize(r);
    for(int i = 0; i < r; i++)
    {
        matrix[i].resize(c);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = input[i][j];
        }
    }
}

template < typename T >
Matrix < T > :: Matrix(const Matrix & ref_matrix)
{
    rows = ref_matrix.rows;
    columns = ref_matrix.columns;
    det_sign = ref_matrix.det_sign;
    matrix = ref_matrix.matrix;
}

template <typename T>
void Matrix<T> :: replace_column(const int column, const QVector<T> from)
{
    for(int i = 0; i < rows; i++)
    {
        matrix[i][column] = from[i];
    }
}

template < typename T >
void Matrix < T > :: swap_columns(const int from, const int to)
{
    for (int i = 0; i < rows; i++)
    {
        T temp = matrix[i][from];
        matrix[i][from] = matrix[i][to];
        matrix[i][to] = temp;
    }
}

template < typename T >
void Matrix < T > :: swap_rows(const int from, const int to)
{
    for (int i = 0; i < columns; i++)
    {
        T temp = matrix[from][i];
        matrix[from][i] = matrix[to][i];
        matrix[to][i] = temp;
    }
}


template < typename T >
void Matrix < T > :: strairs()
{
    if (matrix[0][0] == 0)
    {
        for (int i = 1; i < columns; i++)
        {
            if (matrix[0][i] != 0)
            {
                swap_columns(0, i);
                det_sign = false;
                break;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        T t1 = matrix[i][i];
        for (int i1 = i + 1; i1 < rows; i1++)
        {
            T t2 = matrix[i1][i];
            for (int j = 0; j < columns; j++)
            {
                matrix[i1][j] -= matrix[i][j] * t2 / t1;
            }
        }
    }

}

template < typename T >
T Matrix < T > :: Gauss_method()
{
    strairs();
    T det = matrix[0][0];
    for (int i = 1; (i < rows) || (i < columns); i++)
    {
        det *= matrix[i][i];
    }
    if (det_sign)
    {
        return det;
    }
    else
    {
        return -det;
    }

}

#endif // MATRIX_H
