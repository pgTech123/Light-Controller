#include "fixtures.h"
#include "ui_fixtures.h"

Fixtures::Fixtures(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Fixtures)
{
    ui->setupUi(this);

    ui->dockWidgetContents->setLayout(ui->verticalLayout);
}

Fixtures::~Fixtures()
{
    delete ui;
}

void Fixtures::unselectAll()
{
    ui->listWidget->clearSelection();
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

void Fixtures::on_listWidget_currentRowChanged(int index)
{
    //TODO: set faders
}
