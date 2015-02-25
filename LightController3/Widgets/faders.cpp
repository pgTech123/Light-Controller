#include "faders.h"
#include "ui_faders.h"

Faders::Faders(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Faders)
{
    ui->setupUi(this);
}

Faders::~Faders()
{
    delete ui;
}

