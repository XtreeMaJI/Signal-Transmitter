#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cnetworkreceiver.h"
#include "cgraphdrawer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define GRAPH_RIGHT_BORDER_INDENT 100
#define GRAPH_LEFT_BORDER_INDENT 200
#define AMPL_SCROLL_RIGHT_BORDER_INDENT 88
#define AMPL_SCROLL_WIDTH 22

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPointToChart(double time, double value);

    virtual void resizeEvent(QResizeEvent *event);
private:
    void initUi();

    Ui::MainWindow *ui;
    CNetworkReceiver* networkReceiver;
    CGraphDrawer* graphDrawer;
    QChartView* chartView;

private slots:
    void on_connectBtn_clicked();
    void on_timeSlider_sliderMoved(int position);
    void on_amplSlider_sliderMoved(int position);
    void on_disconnectBtn_clicked();
    void on_penSlider_sliderMoved(int position);
    void on_penColorRedSlider_sliderMoved(int position);
    void on_penColorGreenSlider_sliderMoved(int position);
    void on_penColorBlueSlider_sliderMoved(int position);
    void on_amplScrollSlider_sliderMoved(int position);
};
#endif // MAINWINDOW_H
