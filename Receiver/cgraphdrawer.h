#ifndef CGRAPHDRAWER_H
#define CGRAPHDRAWER_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>

#define MILLISECONDS_IN_SECOND 1000
#define MAX_POINTS_IN_SERIES 500
#define DELETING_POINTS_COUNT 100

class CGraphDrawer
{
public:
    CGraphDrawer();
    ~CGraphDrawer();
    void init();

    void addPointToChart(double time, double value);

    QChart* getChart();

private:
    QChart* chart;
    QLineSeries* series;

    double visibleRangeX;
    double visibleRangeY;
};

#endif // CGRAPHDRAWER_H
