#include "cgraphdrawer.h"

CGraphDrawer::CGraphDrawer() :
    visibleRangeX(1),
    visibleRangeY(1),
    centralPointY(0)
{
    chart = new QChart();
    series = new QSplineSeries();

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

    updateChartRanges();

    if(series->points().size() > MAX_POINTS_IN_SERIES)
    {
        series->removePoints(0, DELETING_POINTS_COUNT);
    }
}

void CGraphDrawer::setVisibleRangeX(double rangeX)
{
    visibleRangeX = rangeX;
    updateChartRanges();
}

void CGraphDrawer::setVisibleRangeY(double rangeY)
{
    visibleRangeY = rangeY;
    updateChartRanges();
}

double CGraphDrawer::getVisibleRangeX()
{
    return visibleRangeX;
}

double CGraphDrawer::getVisibleRangeY()
{
    return visibleRangeY;
}

QChart *CGraphDrawer::getChart()
{
    return chart;
}

void CGraphDrawer::updateChartRanges()
{
    if(series->points().isEmpty())
        return;

    double timeInSeconds = series->points().constLast().x();
    chart->axes(Qt::Horizontal).constFirst()->setRange(timeInSeconds-visibleRangeX, timeInSeconds);
    chart->axes(Qt::Vertical).constFirst()->setRange(centralPointY-visibleRangeY, centralPointY+visibleRangeY);
}

void CGraphDrawer::setPenWidth(int width)
{
    QPen newPen = series->pen();
    newPen.setWidth(width);
    series->setPen(newPen);
}

void CGraphDrawer::setPenColorComponent(EPenColorComponent comp, int value)
{
    QPen newPen = series->pen();
    QColor newColor = newPen.color();
    switch(comp)
    {
        case EPenColorComponent::red:
            newColor.setRed(value);
            break;
        case EPenColorComponent::green:
            newColor.setGreen(value);
            break;
        case EPenColorComponent::blue:
            newColor.setBlue(value);
            break;
        default:
            break;
    }
    newPen.setColor(newColor);
    series->setPen(newPen);
}

void CGraphDrawer::setCentralPointY(double y)
{
    centralPointY = y;
    updateChartRanges();
}
