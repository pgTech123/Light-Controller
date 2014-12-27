#include "aboutlightcontroller.h"
#include "ui_aboutlightcontroller.h"

AboutLightController::AboutLightController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutLightController)
{
    ui->setupUi(this);

    QIcon *icon = new QIcon(ICON_PATH);
    this->setWindowIcon(*icon);
}

AboutLightController::~AboutLightController()
{
    delete ui;
}
