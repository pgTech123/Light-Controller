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
