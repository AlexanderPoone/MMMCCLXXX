#include "visualisationwidget.h"
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>
#include <QThread>
#include "xyseriesiodevice.h"

QT_CHARTS_USE_NAMESPACE

VisualisationWidget::VisualisationWidget(QWidget *parent)
    : QWidget(parent),
      m_device(0),
      m_chart(0),
      m_series(0),
      m_audioInput(0)
{
    m_chart = new QChart;
    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(800, 600);
    m_series = new QLineSeries;
    m_series->setColor(Qt::yellow);
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 2000);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Number of samples");
    axisX->setGridLineColor(Qt::lightGray);
    axisX->setLabelsColor(Qt::green);
    axisX->setTitleBrush(Qt::green);
//    axisX->setShadesColor(Qt::cyan);
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-.5, .5);
//    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio level");
    axisY->setGridLineColor(Qt::lightGray);
    axisY->setLabelsColor(Qt::green);
    axisY->setTitleBrush(Qt::green);
//    axisY->setShadesColor(Qt::cyan);
    m_chart->setAxisX(axisX, m_series);
    m_chart->setAxisY(axisY, m_series);
    m_chart->legend()->hide();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(44000);
//    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    QAudioDeviceInfo inputDevices = QAudioDeviceInfo::defaultInputDevice();
    m_audioInput = new QAudioInput(inputDevices,formatAudio, this);

    m_device = new XYSeriesIODevice(m_series, this);
    m_device->moveToThread(new QThread);
    m_device->open(QIODevice::WriteOnly);

    m_audioInput->start(m_device);
    m_chart->setBackgroundBrush(Qt::black);
}

VisualisationWidget::~VisualisationWidget()
{
    m_audioInput->stop();
    m_device->close();
}
