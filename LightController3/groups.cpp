#include "groups.h"
#include "ui_groups.h"

Groups::Groups(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::Groups)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

Groups::~Groups()
{
    delete ui;
}

void Groups::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}
