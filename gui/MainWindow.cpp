//
// Created by oleg on 9/20/18.
//

#include "MainWindow.hpp"

#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <QList>
#include <QChart>
#include <QChartView>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>

#include "Common.hpp"
#include "parsers/BasicParser.hpp"
#include "parsers/JsonParser.hpp"

using namespace QtCharts;

using namespace lib;

#define DISPLAY_CUMULATIVE 1

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent),
          m_bar_series(new QBarSeries(this)),
          m_chart_view(nullptr),
          m_date_time_format(g_date_time_format)
{
    setGeometry(0, 0, 800, 600);

    auto chart = new QChart();
    chart->addSeries(m_bar_series);
    chart->setTitle("Parking occupation");
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisY()->setRange(0, 1);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    m_chart_view = new QChartView(chart);
    m_chart_view->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(m_chart_view);

    auto load_file_action = new QAction("Open...", this);
    load_file_action->setShortcut(QKeySequence::Open);
    connect(load_file_action, &QAction::triggered, this, &MainWindow::load_file);
    auto file_menu = menuBar()->addMenu("File");
    file_menu->addAction(load_file_action);

    statusBar()->showMessage("You can load JSON files "
                             "by changing file type in the file open dialog");
}

void MainWindow::load_file()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Select file to load",
                                                    "../test_data",
                                                    "Text files (*.txt);;JSON files (*.json)");
    if (filename.isEmpty())
    {
        return;
    }
    load_selected_file(filename);
}

void MainWindow::load_selected_file(const QString& filename)
{
    try
    {
        std::unique_ptr<parsers::IParser> parser;
        if (filename.endsWith(".txt"))
        {
            parser = std::make_unique<parsers::BasicParser>();
            m_date_time_format = g_time_format;
        }
        else if (filename.endsWith(".json"))
        {
            parser = std::make_unique<parsers::JsonParser>();
            m_date_time_format = g_date_time_format;
        }
        else
        {
            QMessageBox::warning(this, "Invalid file type",
                                 "Only .txt and .json files are supported");
            return;
        }

        std::ifstream stream(filename.toStdString());
        if (!stream.is_open())
        {
            QMessageBox::warning(this, "Cannot open file",
                                 "The file you specified cannot be opened");
            return;
        }

        auto cars_density = parser->parse(stream);

#if !defined(DISPLAY_CUMULATIVE) || DISPLAY_CUMULATIVE
        display_cars_cumulative(cars_density);
#else
        display_cars_density(cars_density);
#endif

        auto busiest_time = find_first_busiest_time(cars_density);
        std::stringstream msg_stream;
        msg_stream << "The first busiest time is from "
                   << date_time::to_string(busiest_time.first, m_date_time_format) << " till "
                   << date_time::to_string(busiest_time.second, m_date_time_format);
        statusBar()->showMessage(msg_stream.str().c_str());

    }
    catch (const std::exception& exc)
    {
        QMessageBox::warning(this, "Error",
                             "Error occurred while processing the data: " + QString(exc.what()));
        return;
    }
}

void MainWindow::display_cars_density(const lib::cars_density_t& cars_density)
{
    if (cars_density.empty())
    {
        return;
    }

    auto [min_iter, max_iter] = std::minmax_element(cars_density.begin(), cars_density.end(),
                                                    [](const auto& left, const auto& right) -> bool
                                                    {
                                                        return left.second < right.second;
                                                    });
    m_chart_view->chart()->axisY()->setRange(min_iter->second - 1, max_iter->second + 1);

    QBarSet* bar_set = new QBarSet("");
    QStringList categories;
    for (const auto& [time_point, cars_count] : cars_density)
    {
        auto time_point_str = date_time::to_string(time_point, m_date_time_format);
        *bar_set << cars_count;
        categories.append(time_point_str.c_str());
    }
    m_bar_series->clear();
    m_bar_series->append(bar_set);
    auto axis = new QBarCategoryAxis();
    axis->append(categories);
    m_chart_view->chart()->setAxisX(axis, m_bar_series);
}

void MainWindow::display_cars_cumulative(const lib::cars_density_t& cars_density)
{
    if (cars_density.empty())
    {
        return;
    }

    auto cars_cumulative = build_cars_cumulative(cars_density);

    int max = *std::max_element(cars_cumulative.begin(), cars_cumulative.end());
    m_chart_view->chart()->axisY()->setRange(0, max + 1);

    QBarSet* bar_set = new QBarSet("");
    QStringList categories;
    size_t i = 0;
    for (const auto& pair : cars_density)
    {
        auto time_point_str = date_time::to_string(pair.first, m_date_time_format);
        *bar_set << cars_cumulative[i++];
        categories.append(time_point_str.c_str());
    }
    m_bar_series->clear();
    m_bar_series->append(bar_set);
    auto axis = new QBarCategoryAxis();
    axis->append(categories);
    m_chart_view->chart()->setAxisX(axis, m_bar_series);
}
