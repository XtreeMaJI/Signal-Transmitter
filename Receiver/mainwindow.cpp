#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    networkReceiver = new CNetworkReceiver();
    graphDrawer = new CGraphDrawer();
    networkReceiver->setGraphDrawer(graphDrawer);

    chartView = new QChartView(graphDrawer->getChart());
    chartView->setParent(ui->graphFrame);
    chartView->setGeometry(ui->graphFrame->geometry());

    double amplSliderVal = (MAX_AMPL_ON_SCREEN - graphDrawer->getVisibleRangeY()) * POINTS_IN_AMPL_UNIT;
    ui->amplSlider->setValue(amplSliderVal);

    double timeSliderVal = (MAX_AMOUNT_SECONDS_ON_SCREEN - graphDrawer->getVisibleRangeX()) * MILLISECONDS_IN_SECOND;
    ui->timeSlider->setValue(timeSliderVal);

    double amplScrollSliderMaxVal = VALUES_OF_AMPL_SLIDER / 2;
    double amplScrollSliderMinVal = -VALUES_OF_AMPL_SLIDER / 2;
    double amplScrollSliderVal = 0;
    ui->amplScrollSlider->setMaximum(amplScrollSliderMaxVal);
    ui->amplScrollSlider->setMinimum(amplScrollSliderMinVal);
    ui->amplScrollSlider->setValue(amplScrollSliderVal);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete networkReceiver;
    delete graphDrawer;
    delete chartView;
}


void MainWindow::on_connectBtn_clicked()
{
    QString ip = ui->ipLineEdit->text();

    if(networkReceiver->tryConnectToServer(ip))
        QMessageBox::about(this, "Success", "Connected!");
    else
        QMessageBox::about(this, "Error", "Unable to connect");
}


void MainWindow::on_timeSlider_sliderMoved(int position)
{
    double value = ui->timeSlider->maximum() - position;
    value /= VALUES_OF_TIME_SLIDER;
    if(value == 0)
        return;

    double rangeX = double(value) * double(MAX_AMOUNT_SECONDS_ON_SCREEN);
    graphDrawer->setVisibleRangeX(rangeX);
}


void MainWindow::on_amplSlider_sliderMoved(int position)
{
    double value = ui->amplSlider->maximum() - position;
    value /= VALUES_OF_AMPL_SLIDER;
    if(value == 0)
        return;

    double rangeY = double(value) * double(MAX_AMPL_ON_SCREEN);
    graphDrawer->setVisibleRangeY(rangeY);
}


void MainWindow::on_disconnectBtn_clicked()
{
    networkReceiver->disconnectFromServer();
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect mainWinGeom = this->geometry();
    QRect graphGeom;

    graphGeom.setX(GRAPH_RIGHT_BORDER_INDENT);
    graphGeom.setY(0);
    graphGeom.setWidth(mainWinGeom.width() - GRAPH_LEFT_BORDER_INDENT);
    graphGeom.setHeight(mainWinGeom.height());

    QRect newAmplScrollSliderGeom;
    newAmplScrollSliderGeom.setX(mainWinGeom.width() - AMPL_SCROLL_RIGHT_BORDER_INDENT);
    newAmplScrollSliderGeom.setY(0);
    newAmplScrollSliderGeom.setWidth(AMPL_SCROLL_WIDTH);
    newAmplScrollSliderGeom.setHeight(mainWinGeom.height());

    ui->graphFrame->setGeometry(graphGeom);
    chartView->setGeometry(ui->graphFrame->geometry());

    ui->amplScrollSlider->setGeometry(newAmplScrollSliderGeom);
}


void MainWindow::on_penSlider_sliderMoved(int position)
{
    graphDrawer->setPenWidth(position);
}


void MainWindow::on_penColorRedSlider_sliderMoved(int position)
{
    graphDrawer->setPenColorComponent(CGraphDrawer::red, position);
}

void MainWindow::on_penColorGreenSlider_sliderMoved(int position)
{
    graphDrawer->setPenColorComponent(CGraphDrawer::green, position);
}

void MainWindow::on_penColorBlueSlider_sliderMoved(int position)
{
    graphDrawer->setPenColorComponent(CGraphDrawer::blue, position);
}


void MainWindow::on_amplScrollSlider_sliderMoved(int position)
{
    double value = double(position)/double(VALUES_OF_AMPL_SLIDER/2);
    double centralPointY = double(value) * double(MAX_AMPL_ON_SCREEN);
    graphDrawer->setCentralPointY(centralPointY);
}
