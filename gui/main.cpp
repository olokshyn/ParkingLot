//
// Created by oleg on 9/20/18.
//

#include <iostream>

#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    try
    {
        QApplication app(argc, argv);

        MainWindow main_window;
        main_window.show();

        return app.exec();
    }
    catch (const std::exception& exc)
    {
        std::cerr << "Unhandled exception: " << exc.what() << std::endl;
    }
    return 1;
}
