#include "mainwindow.h"
#include "ui_mainwindow.h"


//текст ошибки на случай разного количества точек
#define ERROR_INPUT_DIFF_DOTS ("Вы ввели разное количество точек\n\nО правилах ввода можно узнать в справке")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #303035");
    //this->setStyleSheet("background-color: white");
    this->resize(960, 540);

    animation = new QPropertyAnimation(ui->sidebar, "maximumWidth");
    QObject::connect(ui->sidebtn, &QPushButton::released, this, &MainWindow::sidebar_animation);

    //добавляем график в окно
    plot = new customPlot();//ui->centralwidget
    ui->gridLayout->addWidget(plot, 0, 1, 1, 1);

    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression("^(?!\\s*$)(\\d+(\\.\\d+)?(\\s\\d+(\\.\\d+)?)*)?$"));
    ui->X_input->setValidator(validator);
    ui->Y_input->setValidator(validator);

    QObject::connect(ui->savebtn, &QPushButton::clicked, plot, &customPlot::getPNG);
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
        ui->sidebtn->setStyleSheet("QPushButton {"
                      "background: #303035;"
                      "padding: 5px;"
                      "color: white;"
                      "font-size: 14px;"
                      "}"
                      "QPushButton:hover {"
                      "background: #45454d;"
                      "}"
                      "QPushButton:pressed {"
                      "background: #1e1e21;"
                      "}");
        ui->menu->setVisible(true);
        ui->sidebtn->setText("Закрыть");
    }
    else
    {
        animation->setStartValue(ui->sidebar->width());
        animation->setEndValue(60);
        ui->sidebtn->setStyleSheet("QPushButton {"
                                   "background: #303035;"
                                   "padding: 5px;"
                                   "color: white;"
                                   "font-size: 9px;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background: #45454d;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background: #1e1e21;"
                                   "} ");
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
    else
    {
        Render::createMap(ui->X_input->text(), ui->Y_input->text());

        Render::Render_graph(*ui->groupBox, *plot, ui->X_input->text());

        Render::Render_dots(Render::QVectorfromQString(ui->X_input->text()), Render::QVectorfromQString(ui->Y_input->text()), *plot);
    }
}

