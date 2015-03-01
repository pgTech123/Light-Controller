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

void SingleFader::setName(QString name)
{
    ui->labelFixtureName->setText(name);
}

void SingleFader::setFixtureAndFader(int fixture, int fader)
{
    FadersToCall fadersToCall;
    fadersToCall.fixture = fixture;
    fadersToCall.faders.append(fader);

    m_fixturesToCall.fixtures.clear();
    m_fixturesToCall.fixtures.append(fadersToCall);
}

void SingleFader::setFixturesAndFaders(FixturesToCall fixturesToCall)
{
    m_fixturesToCall = fixturesToCall;
}

void SingleFader::setValue(int value)
{
    ui->verticalSlider->setValue(value);
}

void SingleFader::setValue(int fixture, int fader, int value)
{
    for(int i = 0; i < m_fixturesToCall.fixtures.size(); i++){
        if(m_fixturesToCall.fixtures.at(i).fixture == fixture){
            for(int j = 0; j < m_fixturesToCall.fixtures.at(i).faders.size(); j++){
                if(m_fixturesToCall.fixtures.at(i).faders.at(j) == fader){
                    setValue(value);
                }
            }
        }
    }
}

void SingleFader::on_verticalSlider_valueChanged(int value)
{
    for(int i = 0; i < m_fixturesToCall.fixtures.size(); i++)
    {
        for(int j = 0; j < m_fixturesToCall.fixtures.at(i).faders.size(); j++)
        {
                emit valueChanged(m_fixturesToCall.fixtures.at(i).fixture,
                                  m_fixturesToCall.fixtures.at(i).faders.at(j),
                                  value);
        }
    }
}
