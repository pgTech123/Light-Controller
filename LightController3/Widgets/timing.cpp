#include "timing.h"
#include "ui_timing.h"

Timing::Timing(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Timing)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->verticalLayout);
}

Timing::~Timing()
{
    delete ui;
}

bool Timing::loadShow(QString path)
{
    return true;
}

bool Timing::saveShow(bool saveAs)
{
    //TODO
    return true;
}

void Timing::setPathToScenes(QString path)
{

}

void Timing::setPathToGroups(QString path)
{

}

QString Timing::getPathToScenes()
{
    return QString("");
}

QString Timing::getPathToGroups()
{
    return QString("");
}

void Timing::reset()
{

}
