#ifndef VISUALISATIONWIDGET_H
#define VISUALISATIONWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE

class VisualisationWidget : public QWidget
{
    Q_OBJECT

public:
    VisualisationWidget(QWidget *parent = 0);
    ~VisualisationWidget();

private:
    XYSeriesIODevice *m_device;
    QChart *m_chart;
    QLineSeries *m_series;
    QAudioInput *m_audioInput;
};

#endif // VISUALISATIONWIDGET_H
