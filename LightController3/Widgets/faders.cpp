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
    m_iTotalAddresses = 0;

    //Set Lights Status
    for(int fixt = 0; fixt < lightsAvailable->getNumOfFixturesAvailable(); fixt++){
        FixtureStatus fixture;
        for(int fad = 0; fad < lightsAvailable->getNumOfFadersForFixture(fixt); fad++){
            //Init all faders to 0
            fixture.faderValue.push_back(0);
            m_iTotalAddresses ++;
        }
        m_LightsStatus.fixtureStatus.push_back(fixture);
    }
}

void Faders::setSerialPort(SerialPort *serialPortWidget)
{
    m_pSerialPortWidget = serialPortWidget;
    m_pSerialPortWidget->setNumberOfAddresses(m_iTotalAddresses);
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
    QList<QString> faderNameList = groupFadersByName(fixtures);

    // Create faders from names
    int numOfFaders = faderNameList.size();
    m_SingleFaderArr = new SingleFader[numOfFaders];

    for(int i = 0; i < numOfFaders; i++){
        m_SingleFaderArr[i].setName(faderNameList.at(i));

        FixturesToCall fixt2Call = generateFixtures2Call(fixtures, faderNameList.at(i));

        m_SingleFaderArr[i].setValue(getFirstValueForFader(fixtures, faderNameList.at(i)));
        m_SingleFaderArr[i].setFixturesAndFaders(fixt2Call);
        connect(&m_SingleFaderArr[i], SIGNAL(valueChanged(int,int,int)),
                this, SLOT(setFaderFromSlider(int,int,int)));
        connect(this, SIGNAL(valueChanged(int,int,int)),
                &m_SingleFaderArr[i], SLOT(setValue(int,int,int)));

        ui->horizontalLayout->addWidget(&m_SingleFaderArr[i]);
    }
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

                //Write on serial port
                int address = 0;
                for(int i = 0; i < fixture; i++){
                    address += m_LightsStatus.fixtureStatus[i].faderValue.size();
                }
                address += fader;
                //cout << address << endl;
                m_pSerialPortWidget->setData(value, address);
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

LightsStatus Faders::getLightsStatus()
{
    return m_LightsStatus;
}

void Faders::deleteFaders()
{
    if(m_SingleFaderArr != NULL){
        delete[] m_SingleFaderArr;
        m_SingleFaderArr = NULL;
    }
}

bool Faders::listContains(QList<QString> strList, QString str)
{
    for(int i = 0; i < strList.size(); i++){
        if(strList.at(i) == str){
            return true;
        }
    }
    return false;
}

QList<QString> Faders::groupFadersByName(QList<int> fixtures)
{
    QList<QString> faderNameList;
    for(int iFx = 0; iFx < fixtures.size(); iFx++)
    {
        if(fixtures.at(iFx) < m_ptrLightsAvailable->getNumOfFixturesAvailable())
        {
            for(int iFad = 0;
                iFad < m_ptrLightsAvailable->getNumOfFadersForFixture(fixtures.at(iFx));
                iFad++)
            {
                QString faderName = m_ptrLightsAvailable->getFaderName(fixtures.at(iFx), iFad);
                if(!listContains(faderNameList, faderName)){
                    faderNameList.append(faderName);
                }
            }
        }
    }
    return faderNameList;
}

FixturesToCall Faders::generateFixtures2Call(QList<int> fixtures, QString faderName)
{
    FixturesToCall fixt2Call;
    bool append = false;

    for(int iFx = 0; iFx < fixtures.size(); iFx++)
    {
        int fixtureID = fixtures.at(iFx);
        FadersToCall fad2Call;
        append = false;

        for(int iFad = 0;
            iFad < m_ptrLightsAvailable->getNumOfFadersForFixture(fixtureID);
            iFad++)
        {
            if(m_ptrLightsAvailable->getFaderName(fixtureID, iFad) == faderName){
                fad2Call.fixture = fixtureID;
                fad2Call.faders.append(iFad);
                append = true;
            }
        }

        if(append){
            fixt2Call.fixtures.append(fad2Call);
        }
    }

    return fixt2Call;
}

int Faders::getFirstValueForFader(QList<int> fixtures, QString faderName)
{
    for(int iFx = 0; iFx < fixtures.size(); iFx++)
    {
        int fixtureID = fixtures.at(iFx);
        for(int iFad = 0;
            iFad < m_ptrLightsAvailable->getNumOfFadersForFixture(fixtureID);
            iFad++)
        {
            if(m_ptrLightsAvailable->getFaderName(fixtureID, iFad) == faderName){
                return m_LightsStatus.fixtureStatus[fixtureID].faderValue[iFad];
            }
        }
    }
    return 0;
}
