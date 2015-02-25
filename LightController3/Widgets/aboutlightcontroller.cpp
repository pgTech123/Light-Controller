/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      aboutlightcontroller.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "aboutlightcontroller.h"
#include "ui_aboutlightcontroller.h"

AboutLightController::AboutLightController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutLightController)
{
    ui->setupUi(this);
}

AboutLightController::~AboutLightController()
{
    delete ui;
}
