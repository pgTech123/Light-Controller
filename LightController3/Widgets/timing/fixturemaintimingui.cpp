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
    m_GraphCursor = NULL;

    m_bCtrlPressed = false;
    m_bShiftPressed = false;
    m_bMousePressed = false;

    m_iNumberOfFaders = 0;
    m_ChannelAvailable = NULL;
}

FixtureMainTimingUI::~FixtureMainTimingUI()
{
    delete ui;
    delete m_btnMenu;
    if(m_ChannelAvailable != NULL){
        for(int i = 0; i < m_iNumberOfFaders; i++){
            delete m_ChannelAvailable[i];
        }
        delete[] m_ChannelAvailable;
    }
}

void FixtureMainTimingUI::mousePressEvent(QMouseEvent* ev)
{
    m_bMousePressed = true;
    if(!m_bShiftPressed){
        emit releaseCuesSelection();
    }

    //Update Cursor
    int mouseX = ui->graphicsView->mapFromGlobal(QCursor::pos()).x();
    int sceneWidth = ui->graphicsView->width();
    if(0 < mouseX && mouseX < sceneWidth){
        unsigned int newCursorPos = mouseX * m_iTimeSeen / sceneWidth + m_uiViewMinTime;
        emit moveCursorTo(newCursorPos);
    }

    //if(on cue): select/toggle
    //else: emit release cue
}

void FixtureMainTimingUI::mouseReleaseEvent(QMouseEvent*)
{
    m_bMousePressed = false;
}

void FixtureMainTimingUI::mouseMoveEvent(QMouseEvent*)
{

}

void FixtureMainTimingUI::wheelEvent(QWheelEvent* ev)
{
    if(m_bCtrlPressed){
        if(ev->delta() > 0){
            emit zoomIn();
        }
        else if (ev->delta() < 0){
            emit zoomOut();
        }
    }
}

void FixtureMainTimingUI::keyPressEvent(QKeyEvent* ev)
{
    if(ev->key() == Qt::Key_Control){
        m_bCtrlPressed = true;
    }
    if(ev->key() == Qt::Key_Shift){
        m_bShiftPressed = true;
    }
}

void FixtureMainTimingUI::keyReleaseEvent(QKeyEvent* ev)
{
    if(ev->key() == Qt::Key_Control){
        m_bCtrlPressed = false;
    }
    if(ev->key() == Qt::Key_Shift){
        m_bShiftPressed = false;
    }
}

void FixtureMainTimingUI::setFixtureName(QString name)
{
    ui->labelFixtureName->setText(name);
}

void FixtureMainTimingUI::addFaderNames(QList<QString> names)
{
    m_iNumberOfFaders = names.size();
    m_ChannelAvailable = new Channel*[m_iNumberOfFaders];

    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        m_ChannelAvailable[i] = new Channel(m_btnMenu, names.at(i));
    }
    ui->toolButtonFaders->setMenu(m_btnMenu);
}

void FixtureMainTimingUI::setFixtureID(int fixtureID)
{
    m_iFixtureId = fixtureID;
}

void FixtureMainTimingUI::setFaders(Faders *faders)
{
    m_FaderRef = faders;
}

void FixtureMainTimingUI::setSongLength(unsigned int songLength)
{
    m_uiSongLength = songLength;
}

void FixtureMainTimingUI::setZoomBoundary(unsigned int min, unsigned int max)
{
    m_uiViewMinTime = min;
    m_uiViewMaxTime = max;
    m_iTimeSeen = m_uiViewMaxTime - m_uiViewMinTime;

    updateCueView();
    updateUI();
}

void FixtureMainTimingUI::addCue()
{
    emit releaseCueSelection();

    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        if(m_ChannelAvailable[i]->isSelected()){
            m_ChannelAvailable[i]->addCue(m_uiCursor);
        }
    }
}

void FixtureMainTimingUI::toggleSharp_Smooth()
{
    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        if(m_ChannelAvailable[i]->isSelected()){
            m_ChannelAvailable[i]->toggleSharpnessOnSelectedCues();
        }
    }
}

void FixtureMainTimingUI::deleteCue()
{
    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        if(m_ChannelAvailable[i]->isSelected()){
            m_ChannelAvailable[i]->deleteSelectedCues();
        }
    }
}

void FixtureMainTimingUI::releaseCueSelection()
{
    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        m_ChannelAvailable[i]->releaseCues();
    }
}

void FixtureMainTimingUI::setSongCursor(unsigned int cursor)
{
    m_uiCursor = cursor;
    updateUI();
}

void FixtureMainTimingUI::updateUI()
{
    //Erase cursor
    if(m_GraphCursor!= NULL)
        m_GraphScene->removeItem((QGraphicsItem*)m_GraphCursor);

    //Draw cursor
    if(m_uiViewMinTime < m_uiCursor && m_uiCursor < m_uiViewMaxTime){
        //Display cursor
        int timeFromMinViewed = m_uiCursor - m_uiViewMinTime;
        int iCursorPosInPixels = timeFromMinViewed * ui->graphicsView->width()/m_iTimeSeen;
        m_GraphScene->setSceneRect(0, 0, ui->graphicsView->width()-5, 168);
        m_GraphCursor = m_GraphScene->addLine(iCursorPosInPixels, 0, iCursorPosInPixels, 168);
    }

    ui->graphicsView->setScene(m_GraphScene);
}

void FixtureMainTimingUI::on_pushButtonAllFaders_clicked()
{
    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        m_ChannelAvailable[i]->setVisible(true);
    }
}

void FixtureMainTimingUI::updateCueView()
{
    //Erase
    m_GraphScene->clear();
    m_GraphCursor = NULL;

    //Outside song in an other color
    if(m_uiViewMaxTime > m_uiSongLength){
        QPen pen;   //TODO: Set a color if there is an artist in the room.
        QBrush brush(Qt::BDiagPattern);
        unsigned int uiEndOfSong = (m_uiSongLength-m_uiViewMinTime)*ui->graphicsView->width()/m_iTimeSeen;
        unsigned int uiWidthOfUnusedSpace = (m_uiViewMaxTime-m_uiSongLength)*ui->graphicsView->width()/m_iTimeSeen;
        m_GraphScene->addRect(uiEndOfSong,0, uiWidthOfUnusedSpace, 168, pen, brush);
    }

    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        if(m_ChannelAvailable[i]->isSelected()){
            m_ChannelAvailable[i]->drawCuesBetween(m_GraphScene, m_uiViewMinTime, m_uiViewMaxTime);
        }
    }
}

