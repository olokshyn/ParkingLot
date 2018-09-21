//
// Created by oleg on 9/20/18.
//

#ifndef PARKINGLOT_MAINWINDOW_HPP
#define PARKINGLOT_MAINWINDOW_HPP

#include <QMainWindow>
#include <QBarSeries>
#include <QChartView>

#include "CarsDensity.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void load_file();
    void load_selected_file(const QString& filename);

private:
    void display_cars_density(const lib::cars_density_t& cars_density);
    void display_cars_cumulative(const lib::cars_density_t& cars_density);

private:
    QtCharts::QBarSeries* m_bar_series;
    QtCharts::QChartView* m_chart_view;

    const char* m_date_time_format;
};

#endif //PARKINGLOT_MAINWINDOW_HPP
