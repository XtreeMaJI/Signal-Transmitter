#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cnetworkreceiver.h"
#include "cgraphdrawer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPointToChart(double time, double value);

private:
    void initUi();

    Ui::MainWindow *ui;
    CNetworkReceiver* networkReceiver;
    CGraphDrawer* graphDrawer;
    QChartView* chartView;

private slots:
    void on_connectBtn_clicked();
};
#endif // MAINWINDOW_H