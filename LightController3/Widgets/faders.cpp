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

        int numberOfFaders = m_ptrLightsAvailable->getNumOfFadersForFixture(fixture);
        m_SingleFaderArr = new SingleFader[numberOfFaders];

        for(int fader = 0; fader < numberOfFaders; fader++)
        {
            m_SingleFaderArr[fader].setName(m_ptrLightsAvailable->getFaderName(fixture, fader));
            m_SingleFaderArr[fader].setValue(m_LightsStatus.fixtureStatus[fixture].faderValue[fader]);
            m_SingleFaderArr[fader].setFixtureAndFader(fixture, fader);
            connect(&m_SingleFaderArr[fader], SIGNAL(valueChanged(int,int,int)),
                    this, SLOT(setFaderFromSlider(int,int,int)));
            connect(this, SIGNAL(valueChanged(int,int,int)),
                    &m_SingleFaderArr[fader], SLOT(setValue(int,int,int)));

            ui->horizontalLayout->addWidget(&m_SingleFaderArr[fader]);
        }

        emit unselect(GROUP);
    }
}

void Faders::accessFixtures(QList<int> fixtures, QString name)
{
    deleteFaders();
    ui->labelFixtureName->setText(name);

    QList<QString> faderNameList;
    for(int iFx = 0; iFx < fixtures.size(); iFx++)
    {
        for(int fader = 0;
            fader < m_ptrLightsAvailable->getNumOfFadersForFixture(fixtures.at(iFx));
            fader++)
        {
            //TODO: if faderNameList !contains name, append it
        }
    }
    //TODO: Create faders from names
    emit unselect(FIXTURE);
}

void Faders::setFader(int fixture, int fader, int value)
{
    setFaderFromSlider(fixture, fader, value);
    emit valueChanged(fixture, fader, value);
}

void Faders::setFaderFromSlider(int fixture, int fader, int value)
{
    if(fixture < m_ptrLightsAvailable->getNumOfFixturesAvailable() && fixture >= 0){
        if(fader < m_ptrLightsAvailable->getNumOfFadersForFixture(fixture) && fader >= 0){
            if(value <= 255 && value >=0){
                m_LightsStatus.fixtureStatus[fixture].faderValue[fader] = value;
            }
        }
    }
}

int Faders::getFader(int fixture, int fader)
{
    if(fixture < m_ptrLightsAvailable->getNumOfFixturesAvailable() && fixture >= 0){
        if(fader < m_ptrLightsAvailable->getNumOfFadersForFixture(fixture) && fader >= 0){
            return m_LightsStatus.fixtureStatus[fixture].faderValue[fader];
        }
    }
    return 0;
}

void Faders::deleteFaders()
{
    if(m_SingleFaderArr != NULL){
        delete[] m_SingleFaderArr;
        m_SingleFaderArr = NULL;
    }
}
