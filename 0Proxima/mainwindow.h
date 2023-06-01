#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPropertyAnimation>
#include "regression.h"
#include "render.h"
#include <QPropertyAnimation>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QValidator>
#include "customplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void sidebar_animation();

    void on_Quit_btn_clicked();

    void on_Build_Plot_btn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    customPlot *plot;


    QVector<double> x, y;

    QPropertyAnimation *animation;

};
#endif // MAINWINDOW_H
