#include "timing.h"
#include "ui_timing.h"

Timing::Timing(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Timing)
{
    ui->setupUi(this);
}

Timing::~Timing()
{
    delete ui;
}

void Timing::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}
