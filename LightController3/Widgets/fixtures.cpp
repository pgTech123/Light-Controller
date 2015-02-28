/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      fixture.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "fixtures.h"
#include "ui_fixtures.h"

Fixtures::Fixtures(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Fixtures)
{
    ui->setupUi(this);

    ui->dockWidgetContents->setLayout(ui->verticalLayout);
    m_ptrFaders = NULL;

    connect(ui->listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(on_listWidget_itemClicked(QListWidgetItem*)));
}

Fixtures::~Fixtures()
{
    delete ui;
}

void Fixtures::unselectAll(FixtureSelector sel)
{
    if(sel == FIXTURE){
        ui->listWidget->clearSelection();
    }
}

void Fixtures::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;

    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        // Add every fixtures in list
        QListWidgetItem *item= new QListWidgetItem(m_ptrLightsAvailable->getFixtureName(i));
        ui->listWidget->addItem(item);
    }
}

void Fixtures::setFaders(Faders *faders)
{
    m_ptrFaders = faders;
    connect(m_ptrFaders, SIGNAL(unselect(FixtureSelector)),
            this, SLOT(unselectAll(FixtureSelector)));
}

void Fixtures::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int row = ui->listWidget->row(item);
    if(m_ptrFaders != NULL){
        m_ptrFaders->accessFixture(row);
    }
}
