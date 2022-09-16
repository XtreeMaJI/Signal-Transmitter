#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    networkReceiver->connectToServer(ip);
}

void MainWindow::on_timeSlider_sliderMoved(int position)
{
    double value = ui->timeSlider->maximum() - position;
    if(value == 0)
        value = 1;

    double rangeX = double(value) / double(MILLISECONDS_IN_SECOND);
    graphDrawer->setVisibleRangeX(rangeX);
}


void MainWindow::on_amplSlider_sliderMoved(int position)
{
    double value = ui->amplSlider->maximum() - position;
    if(value == 0)
        value = 1;

    double rangeY = double(value) / double(POINTS_IN_AMPL_UNIT);
    graphDrawer->setVisibleRangeY(rangeY);
}


void MainWindow::on_disconnectBtn_clicked()
{
    networkReceiver->disconnectFromServer();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QRect newFrameGeom = this->geometry();

    newFrameGeom.setX(100);
    newFrameGeom.setY(0);
    newFrameGeom.setWidth(newFrameGeom.width() - 550);
    newFrameGeom.setHeight(newFrameGeom.height() - 300);

    ui->graphFrame->setGeometry(newFrameGeom);
    chartView->setGeometry(ui->graphFrame->geometry());
}

