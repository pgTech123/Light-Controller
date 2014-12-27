/*************************************************************************
 * Project:     GV Light Controller 3
 *
 * File Name:   main.cpp
 *
 * Author:      Pascal Gendron
 *
 * Version:     0.3.0
 * ************************************************************************/

#include <QApplication>
#include <QIcon>
#include "mainwindow.h"

/* Program Parameters */
#define ICON_PATH   "./../GVisionLogo.ico"
#define APP_NAME    "GVision Ligth Controller 3.0"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWind;
    QIcon *icon = new QIcon(ICON_PATH);

    mainWind.setWindowTitle(APP_NAME);
    mainWind.setWindowIcon(*icon);
    mainWind.show();

    return app.exec();
}
