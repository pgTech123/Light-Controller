#include "aboutlightcontroller.h"
#include "ui_aboutlightcontroller.h"

AboutLightController::AboutLightController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutLightController)
{
    ui->setupUi(this);

    QIcon *icon = new QIcon(ICON_PATH);
    this->setWindowIcon(*icon);

    QPixmap pixmapLogo;
    pixmapLogo.load(PATH_TO_LOGO);
    pixmapLogo = pixmapLogo.scaled(ui->logo->width() ,ui->logo->height(),Qt::KeepAspectRatio);
    ui->logo->setPixmap(pixmapLogo);
}

AboutLightController::~AboutLightController()
{
    delete ui;
}
