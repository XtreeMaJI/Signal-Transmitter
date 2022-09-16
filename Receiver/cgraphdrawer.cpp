#include "cgraphdrawer.h"

CGraphDrawer::CGraphDrawer() :
    visibleRangeX(1),
    visibleRangeY(1)
{
    chart = new QChart();
    series = new QLineSeries();

    QPen pen;
    pen.setWidth(3);
    pen.setColor(Qt::black);

    series->setPen(pen);

    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle("Signal");
    chart->legend()->hide();
}

CGraphDrawer::~CGraphDrawer()
{
    delete chart;
    delete series;
}

void CGraphDrawer::addPointToChart(double time, double value)
{
    //Переводим время в секунды для графика
    double timeInSeconds = time / MILLISECONDS_IN_SECOND;

    series->append(timeInSeconds, value);
    chart->axes(Qt::Horizontal).first()->setRange(timeInSeconds-visibleRangeX, timeInSeconds);
    chart->axes(Qt::Vertical).first()->setRange(-visibleRangeY, visibleRangeY);
}

QChart *CGraphDrawer::getChart()
{
    return chart;
}
