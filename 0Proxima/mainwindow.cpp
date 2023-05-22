#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regression.h"
#include "render.h"
#include <QPropertyAnimation>
#include <QMessageBox>

//текст ошибки на случай разного количества точек
#define ERROR_INPUT_DIFF_DOTS ("Вы ввели разное количество точек\n\nО правилах ввода можно узнать в справке")
//текст ошибки на случай ввода не цифр
#define ERROR_INPUT_NOT_NUM ("Неправильный ввод\nВведены другие символы, кроме цифр и точек\n\nО правилах ввода можно узнать в справке")
//TO DO
//прочие ошибки
//справку


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #303035");
    this->resize(960, 540);

    animation = new QPropertyAnimation(ui->sidebar, "maximumWidth");
    QObject::connect(ui->sidebtn, &QPushButton::released, this, &MainWindow::sidebar_animation);

    //добавляем график в окно
    plot = new customPlot();//ui->centralwidget
    ui->gridLayout->addWidget(plot, 0, 1, 1, 1);


}

MainWindow::~MainWindow()
{
    delete animation;
    delete plot;
    delete ui;
}


void MainWindow::sidebar_animation()
{
    animation->stop();
    if (ui->sidebar->width() == 60)
    {
        animation->setStartValue(ui->sidebar->width());
        animation->setEndValue(343);
        ui->sidebtn->setStyleSheet("background: #303035;border-style: outset;border-width: 2px; border-color: beige; border-radius: 15px; padding: 5px; color: white; font-size: 14px;");
        ui->menu->setVisible(true);
        ui->sidebtn->setText("Закрыть");
    }
    else
    {
        animation->setStartValue(ui->sidebar->width());
        animation->setEndValue(60);
        ui->sidebtn->setStyleSheet("background: #303035;border-style: outset;border-width: 2px; border-color: beige; border-radius: 15px; padding: 5px; color: white; font-size: 9px;");
        ui->menu->setVisible(false);
        ui->sidebtn->setText("Меню");
    }
    animation->setEasingCurve(QEasingCurve::InOutCubic);
    animation->setDuration(470);
    animation->start();
}




void MainWindow::on_Quit_btn_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, " ", "Вы уверены?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        this->close();
    }
}


void MainWindow::on_Build_Plot_btn_clicked()
{
    if(Render::QVectorfromQString(ui->X_input->text()).size() != Render::QVectorfromQString(ui->Y_input->text()).size())
    {
        QMessageBox::warning(this, "Ошибка!", ERROR_INPUT_DIFF_DOTS);
    }
    //TO DO
    /*
    else if(smth)
    {
        QMessageBox::warning(this, "Ошибка!", ERROR_INPUT_NOT_NUM);
    }
*/

    Render::createMap(ui->X_input->text(), ui->Y_input->text());

    Render::Render_graph(*ui->groupBox, *plot, ui->X_input->text());

    Render::Render_dots(Render::QVectorfromQString(ui->X_input->text()), Render::QVectorfromQString(ui->Y_input->text()), *plot);
}


void MainWindow::on_Return_btn_clicked()
{
    plot->returnToCenter();
}

