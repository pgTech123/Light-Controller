/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      faders.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "faders.h"
#include "ui_faders.h"

Faders::Faders(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Faders)
{
    ui->setupUi(this);

    m_SingleFaderArr = NULL;
    ui->dockWidgetContents->setLayout(ui->verticalLayout);
}

Faders::~Faders()
{
    delete ui;
    deleteFaders();
}

void Faders::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;

    //Set Lights Status
    for(int fixt = 0; fixt < lightsAvailable->getNumOfFixturesAvailable(); fixt++){
        FixtureStatus fixture;
        for(int fad = 0; fad < lightsAvailable->getNumOfFadersForFixture(fixt); fad++){
            //Init all faders to 0
            fixture.faderValue.push_back(0);
        }
        m_LightsStatus.fixtureStatus.push_back(fixture);
    }
}

void Faders::accessFixture(int fixture)
{
    deleteFaders();
    if(fixture < m_ptrLightsAvailable->getNumOfFixturesAvailable() && fixture >= 0){
        ui->labelFixtureName->setText(m_ptrLightsAvailable->getFixtureName(fixture));
        //TODO

        emit unselect(GROUP);
    }
}

void Faders::accessFixtures(QList<int> fixtures, QString name)
{
    deleteFaders();
    ui->labelFixtureName->setText(name);
    emit unselect(FIXTURE);
}

void Faders::setFader(int fixture, int fader, int value)
{
    //TODO
}

int Faders::getFader(int fixture, int fader)
{
    //TODO
}

void Faders::deleteFaders()
{
    if(m_SingleFaderArr != NULL){
        delete[] m_SingleFaderArr;
    }
}
