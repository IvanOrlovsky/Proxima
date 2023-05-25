#include "render.h"
#include <QList>


std::map<QString, Approximation*> Render::mp;

QVector<double> Render::QVectorfromQString(QString input)
{
    QVector<double> result;
    QString temp("");
    input += " ";
    for(int i = 0; i < input.size(); i++)
    {

        if(!input[i].isSpace())
        {
            temp.push_back(input[i]);
        }
        else
        {
            result.push_back(temp.toDouble());
            temp = "";
        }
    }

    return result;
}

QVector<double> Render::getYvector(const QString chckbx_name, const QVector<double> values)
{
    QVector<double> result;

    double x_value = qRound(values[0] * qPow(10, 5)) / qPow(10, 5);

    while(x_value <= values[values.size() - 1]/* + 0.00001*/)
    {
        result.push_back(mp[chckbx_name]->calc(x_value));
        x_value += 0.01;
        x_value = qRound(x_value * qPow(10, 5)) / qPow(10, 5);
    }

    return result;
}

QVector<double> Render::getXvector(const QString value_input)
{
    QVector<double> values = QVectorfromQString(value_input);
    QVector<double> result;
    double x_value = qRound(values[0] * qPow(10, 5)) / qPow(10, 5);

    //qDebug() << "\n----------" << 1.19 + 0.01 << "--------\n";
    while(x_value <= values[values.size() - 1]/* + 0.00001*/)
    {
        result.push_back(x_value);

        x_value += 0.01;
        x_value = qRound(x_value * qPow(10, 5)) / qPow(10, 5);
    }


    return result;
}

void Render::Render_dots(const QVector<double> x, const QVector<double> y, customPlot &plot)
{
        plot.addPoints(x, y);
}



void Render::Render_graph(const QGroupBox &groupbox, customPlot &plot, const QString x_input)
{
    foreach (QCheckBox * box, groupbox.findChildren<QCheckBox *>())
    {
        if(box->isChecked())
        {
            plot.addPlot(getXvector(x_input), getYvector(box->text(), getXvector(x_input)));
        }
    }
}

void Render::createMap(const QString x, const QString y)
{
    if(!mp.empty())
    {
        for(std::map<QString, Approximation*>::iterator it = mp.begin(); it != mp.end(); it++)
        {
            mp.erase(it);
        }
    }

    QVector<double> X = QVectorfromQString(x);
    QVector<double> Y = QVectorfromQString(y);
    mp["Кусочно-линейная"] = new Linear_Interpolation(X, Y);
    mp["Кусочно-квадратичная"] = new Quadratic_Interpolation(X, Y);
    mp["Полином Лагранжа"] = new Lagranzh_polinom(X, Y);
    mp["Полином Ньютона"] = new Newton_polinom(X, Y);
    mp["Линейная"] = new Linear_Regression(X, Y);
    mp["Квадратичная"] = new Quadratic_Regression(X, Y);
    mp["Гиперболическая"] = new Hyperbolic_Regression(X, Y);
    mp["Экспоненциальная"] = new Exponential_Regression(X, Y);
}

//TO DO
bool Render::QStringContainsOnlyNums(const QString qstr)
{
    Q_UNUSED(qstr);
return 0;
}
