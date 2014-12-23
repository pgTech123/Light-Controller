#include "scenes.h"
#include "ui_scenes.h"

Scenes::Scenes(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Scenes)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

Scenes::~Scenes()
{
    delete ui;
}

void Scenes::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}
