/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      singlefader.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "singlefader.h"
#include "ui_singlefader.h"

SingleFader::SingleFader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleFader)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
}

SingleFader::~SingleFader()
{
    delete ui;
}

void SingleFader::setValue(int value)
{
    ui->verticalSlider->setValue(value);
}

void SingleFader::on_verticalSlider_valueChanged(int value)
{
    emit valueChanged(value);
}
