#include "faders.h"
#include "ui_faders.h"

Faders::Faders(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Faders)
{
    ui->setupUi(this);
}

Faders::~Faders()
{
    delete ui;
}

void Faders::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}
