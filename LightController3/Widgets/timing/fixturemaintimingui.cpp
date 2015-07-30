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
    m_GraphSceneCues = new QGraphicsScene(this);

    m_bCtrlPressed = false;
    m_bShiftPressed = false;
    m_bMousePressed = false;
    m_bImmunedCueRelease = false;

    m_iNumberOfFaders = 0;
    m_ActionFadersSelection = NULL;
    m_ChannelAvailable = NULL;
}

FixtureMainTimingUI::~FixtureMainTimingUI()
{
    if(m_ActionFadersSelection != NULL){
        for(int i = 0; i < m_iNumberOfFaders; i++){
            delete m_ActionFadersSelection[i];
        }
        delete[] m_ActionFadersSelection;
    }

    if(m_ChannelAvailable != NULL){
        for(int i = 0; i < m_iNumberOfFaders; i++){
            delete m_ChannelAvailable[i];
        }
        delete[] m_ChannelAvailable;
    }

    delete ui;
    delete m_btnMenu;
}

void FixtureMainTimingUI::mousePressEvent(QMouseEvent* ev)
{
    m_bMousePressed = true;
    if(!m_bShiftPressed){
        m_ListSelectedCues.clear();
        m_bImmunedCueRelease = true;
        emit releaseCuesSelection();
    }

    //Update Cursor
    int mouseX = ui->graphicsView->mapFromGlobal(QCursor::pos()).x();
    int sceneWidth = ui->graphicsView->width();
    if(0 < mouseX && mouseX < sceneWidth){
        unsigned int newCursorPos = mouseX * m_iTimeSeen / sceneWidth + m_uiViewMinTime;
        emit moveCursorTo(newCursorPos);
    }

    //if(on cue): select
    //else: release cue
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
    m_ActionFadersSelection = new QAction*[m_iNumberOfFaders];
    m_ChannelAvailable = new Channel*[m_iNumberOfFaders];

    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        m_ActionFadersSelection[i] = m_btnMenu->addAction(names.at(i));
        m_ActionFadersSelection[i]->setCheckable(true);
        m_ActionFadersSelection[i]->setChecked(true);

        m_ChannelAvailable[i] = new Channel;

        connect(m_ActionFadersSelection[i], SIGNAL(triggered(bool)), m_ChannelAvailable[i], SLOT(setVisible(bool)));
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
    m_ListSelectedCues.clear();

    //Build cue
    Cue newCue;
    newCue.faderConcerned.clear();
    newCue.faderValue.clear();


    //Add Cue
    //TODO
}

void FixtureMainTimingUI::toggleSharp_Smooth()
{
    for(int i = 0; i < m_ListSelectedCues.size(); i++){
        int currentCue = m_ListSelectedCues.at(i);
        if(currentCue > m_ListCues.size()){
            return;
        }
        if(m_ListCues.at(currentCue).sharp){
            m_ListCues[currentCue].sharp = false;
        }
        else{
            m_ListCues[currentCue].sharp = true;
        }
    }
}

void FixtureMainTimingUI::deleteCue()
{
    for(int i = 0; i < m_ListSelectedCues.size(); i++){
        //TODO: delete cues
    }
}

void FixtureMainTimingUI::releaseCueSelection()
{
    if(!m_bImmunedCueRelease){
        m_ListSelectedCues.clear();
    }
    m_bImmunedCueRelease = false;
}

void FixtureMainTimingUI::setSongCursor(unsigned int cursor)
{
    m_uiCursor = cursor;
    updateUI();
}

void FixtureMainTimingUI::updateUI()
{
    //Erase cursor
    m_GraphScene->clear();

    //TODO: copy cues to scene...
    //(*m_GraphScene) = (*m_GraphSceneCues);

    if(m_uiViewMinTime < m_uiCursor && m_uiCursor < m_uiViewMaxTime){
        //Display cursor
        int timeFromMinViewed = m_uiCursor - m_uiViewMinTime;
        int iCursorPosInPixels = timeFromMinViewed * ui->graphicsView->width()/m_iTimeSeen;
        m_GraphScene->setSceneRect(0, 0, ui->graphicsView->width()-5, 168);
        m_GraphScene->addLine(iCursorPosInPixels, 0, iCursorPosInPixels, 168);
    }

    ui->graphicsView->setScene(m_GraphScene);
}

void FixtureMainTimingUI::on_pushButtonAllFaders_clicked()
{
    for(int i = 0; i < m_iNumberOfFaders; i++)
    {
        m_ActionFadersSelection[i]->setChecked(true);
        m_ChannelAvailable[i]->setVisible(true);
    }
}

void FixtureMainTimingUI::updateCueView()
{
    //Erase
    m_GraphSceneCues->clear();

    //Outside song in an other color
    if(m_uiViewMaxTime > m_uiSongLength){
        //TODO: proportions + fill avec couleur
    }

    for(int i = 0; i < m_ListCues.size(); i++){
        if(m_uiViewMinTime < m_ListCues.at(i).timeID &&
                m_ListCues.at(i).timeID < m_uiViewMaxTime){
            //Draw cue
        }
    }

    //Selected cues
    for(int i = 0; i < m_ListSelectedCues.size(); i++){
        int currentCue = m_ListSelectedCues.at(i);
        if(m_uiViewMinTime < m_ListCues.at(currentCue).timeID &&
                m_ListCues.at(currentCue).timeID < m_uiViewMaxTime){
            //Color cue
        }
    }
}
