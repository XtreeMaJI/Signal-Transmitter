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

