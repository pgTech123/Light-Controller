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

bool Scenes::loadScenes(QString path)
{
    return true;
}

bool Scenes::saveScenes(bool saveAs)
{
    return true;
}

QString Scenes::getPath()
{
    return QString("");
}

void Scenes::reset()
{

}
