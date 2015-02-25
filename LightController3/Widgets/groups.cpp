#include "groups.h"
#include "ui_groups.h"

Groups::Groups(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Groups)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

Groups::~Groups()
{
    delete ui;
}

bool Groups::loadGroups(QString path)
{

}
