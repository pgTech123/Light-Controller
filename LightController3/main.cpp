/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      main.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include <QApplication>
#include <QIcon>
#include "Widgets/mainwindow.h"

/* Program Parameters */
#define ICON_PATH   "./../Ressources/GVisionLogo.ico"
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
