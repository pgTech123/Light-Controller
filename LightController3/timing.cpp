#include "timing.h"
#include "ui_timing.h"

Timing::Timing(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Timing)
{
    ui->setupUi(this);
}

Timing::~Timing()
{
    delete ui;
}
