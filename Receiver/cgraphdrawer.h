#ifndef CGRAPHDRAWER_H
#define CGRAPHDRAWER_H

#include <QMainWindow>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QTimer>
#include <QSplineSeries>

#define MILLISECONDS_IN_SECOND 1000
#define MAX_POINTS_IN_SERIES 2400
#define DELETING_POINTS_COUNT 100
#define MAX_AMOUNT_SECONDS_ON_SCREEN 8 //Максимальный интервал по оси У, который можем показать на графике
#define VALUES_OF_TIME_SLIDER 10000
#define MAX_AMPL_ON_SCREEN 10 //Максимальный масштаб по оси Х
#define POINTS_IN_AMPL_UNIT 1000
#define VALUES_OF_AMPL_SLIDER 10000

class CGraphDrawer
{
public:
    enum EPenColorComponent
    {
        red,
        green,
        blue
    };
public:
    CGraphDrawer();
    ~CGraphDrawer();
    void init();
    void addPointToChart(double time, double value);
    void setVisibleRangeX(double rangeX);
    void setVisibleRangeY(double rangeY);
    double getVisibleRangeX();
    double getVisibleRangeY();
    QChart* getChart();
    void updateChartRanges();
    void setPenWidth(int width);
    void setPenColorComponent(EPenColorComponent comp, int value);
    void setCentralPointY(double y);

private:
    QChart* chart;
    QSplineSeries* series;

    double visibleRangeX; //Интервал времени в секундах, который виден на графике
    double visibleRangeY;

    double centralPointY;
};

#endif // CGRAPHDRAWER_H
