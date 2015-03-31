#include "fixturemaintimingui.h"
#include "ui_fixturemaintimingui.h"

FixtureMainTimingUI::FixtureMainTimingUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixtureMainTimingUI)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
    this->setFixedHeight(175);
    ui->labelFixtureName->setFixedWidth(125);
    ui->toolButtonFaders->setFixedWidth(125);

    m_btnMenu = new QMenu();
    m_GraphScene = new QGraphicsScene(this);
}

FixtureMainTimingUI::~FixtureMainTimingUI()
{
    delete ui;
    delete m_btnMenu;
}

void FixtureMainTimingUI::setFixtureName(QString name)
{
    ui->labelFixtureName->setText(name);
}

void FixtureMainTimingUI::addFaderNames(QList<QString> names)
{
    int numberOfFaders = names.size();

    for(int i = 0; i < numberOfFaders; i++)
    {
        QAction *action = m_btnMenu->addAction(names.at(i));
        //TODO: connect action
    }
    ui->toolButtonFaders->setMenu(m_btnMenu);
}

void FixtureMainTimingUI::setFixtureID(int fixtureID)
{

}

void FixtureMainTimingUI::setFaders(Faders *faders)
{

}

void FixtureMainTimingUI::setSongLength(unsigned int length)
{

}

void FixtureMainTimingUI::setZoomBoundary(unsigned int min, unsigned int max)
{
    m_uiViewMinTime = min;
    m_uiViewMaxTime = max;
    cout << m_uiViewMaxTime << endl;
    m_iTimeSeen = m_uiViewMaxTime - m_uiViewMinTime;

    updateUI();
}

void FixtureMainTimingUI::addCue()
{

}

void FixtureMainTimingUI::toggleSharp_Smooth()
{

}

void FixtureMainTimingUI::deleteCue()
{

}

void FixtureMainTimingUI::setSongCursor(unsigned int cursor)
{
    m_uiCursor = cursor;
    //TODO: call cues...
    updateUI();
}

void FixtureMainTimingUI::updateUI()
{
    //Erase cursor
    m_GraphScene->clear();

    //TODO: Display cues

    if(m_uiViewMinTime < m_uiCursor && m_uiCursor < m_uiViewMaxTime){
        //Display cursor
        int timeFromMinViewed = m_uiCursor - m_uiViewMinTime;
        int iCursorPosInPixels = timeFromMinViewed * ui->graphicsView->width()/m_iTimeSeen;
        m_GraphScene->setSceneRect(0, 0, ui->graphicsView->width()-5, 168);
        m_GraphScene->addLine(iCursorPosInPixels, 0, iCursorPosInPixels, 168);
    }

    ui->graphicsView->setScene(m_GraphScene);
}
