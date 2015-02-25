#include "scenes.h"
#include "ui_scenes.h"

Scenes::Scenes(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Scenes)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

Scenes::~Scenes()
{
    delete ui;
}

bool Scenes::loadScene(QString path)
{

}
