#include "groupediting.h"
#include "ui_groupediting.h"

GroupEditing::GroupEditing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupEditing)
{
    ui->setupUi(this);
}

GroupEditing::~GroupEditing()
{
    delete ui;
}
