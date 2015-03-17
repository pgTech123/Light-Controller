#include "timing.h"
#include "ui_timing.h"

Timing::Timing(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Timing)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->verticalLayout);
    ui->scrollAreaWidgetContents->setLayout(ui->verticalLayoutScrollArea);

    m_CallbackTimer = new QTimer(this);
    m_CallbackTimer->start(TIME_RESOLUTION);

    m_ptrLightsAvailable = NULL;
    m_ptrFaders = NULL;
    m_FixtureMainTimingArr = NULL;

    initializeFMOD();
}

Timing::~Timing()
{
    delete ui;
    if(m_FixtureMainTimingArr != NULL){
        delete[] m_FixtureMainTimingArr;
    }
    releaseFMOD();
}

bool Timing::loadShow(QString path)
{
    return true;
}

bool Timing::saveShow(bool saveAs)
{
    //TODO
    return true;
}

void Timing::setPathToScenes(QString path)
{

}

void Timing::setPathToGroups(QString path)
{

}

QString Timing::getPathToScenes()
{
    return QString("");
}

QString Timing::getPathToGroups()
{
    return QString("");
}

void Timing::reset()
{

}

void Timing::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;
    int fixtAvailable = m_ptrLightsAvailable->getNumOfFixturesAvailable();
    m_FixtureMainTimingArr = new FixtureMainTimingUI[fixtAvailable];

    for(int i = 0; i < fixtAvailable; i++)
    {
        //Fixture
        m_FixtureMainTimingArr[i].setFixtureName(m_ptrLightsAvailable->getFixtureName(i));
        m_FixtureMainTimingArr[i].setFixtureID(i);

        //Fader names
        QList<QString> faderNameList;
        for(int j = 0; j < m_ptrLightsAvailable->getNumOfFadersForFixture(i); j++){
            faderNameList.append(m_ptrLightsAvailable->getFaderName(i, j));
        }
        m_FixtureMainTimingArr[i].addFaderNames(faderNameList);

        connect(this, SIGNAL(addCue()), &m_FixtureMainTimingArr[i], SLOT(addCue()));
        connect(this, SIGNAL(toggleSharp_Smooth()), &m_FixtureMainTimingArr[i], SLOT(toggleSharp_Smooth()));
        connect(this, SIGNAL(deleteCue()), &m_FixtureMainTimingArr[i], SLOT(deleteCue()));

        connect(&m_FixtureMainTimingArr[i], SIGNAL(zoomIn()), this, SLOT(zoomIn()));
        connect(&m_FixtureMainTimingArr[i], SIGNAL(zoomOut()), this, SLOT(zoomOut()));

        //Add to UI
        ui->verticalLayoutScrollArea->addWidget(&m_FixtureMainTimingArr[i]);
    }
}

void Timing::setFaders(Faders *faders)
{
    m_ptrFaders = faders;

    int fixtAvailable = m_ptrLightsAvailable->getNumOfFixturesAvailable();
    for(int i = 0; i < fixtAvailable; i++){
        m_FixtureMainTimingArr[i].setFaders(m_ptrFaders);
    }
}

unsigned int Timing::getSongTotalLenght()
{
    return m_uiSongLenght_ms;
}

unsigned int Timing::getSongCurrentTime()
{
    m_fmodChannel->getPosition(&m_uiCursor_ms, FMOD_TIMEUNIT_MS);
    setTimeUI();
    return m_uiCursor_ms;
}

void Timing::setSongCurrentTime(unsigned int time_ms)
{
    m_fmodChannel->setPosition(time_ms, FMOD_TIMEUNIT_MS);
    m_uiCursor_ms = time_ms;
    setTimeUI();
}

void Timing::initializeFMOD()
{
    m_uiSongLenght_ms = 0;
    m_uiCursor_ms = 0;

    m_fmodSystem = NULL;
    m_fmodMusic = NULL;
    m_fmodChannel = NULL;

    FMOD::System_Create(&m_fmodSystem);
    m_fmodSystem->init(2, FMOD_INIT_NORMAL, NULL);

    m_bIsPlaying = false;
}

void Timing::releaseFMOD()
{
    if(m_fmodMusic != NULL){
        m_fmodMusic->release();
    }
    if(m_fmodSystem != NULL){
        m_fmodSystem->close();
        m_fmodSystem->release();
    }
}

void Timing::loadSong(QString songPath)
{
    m_fmodSystem->createSound(songPath.toUtf8().constData(),
                            FMOD_2D | FMOD_CREATESTREAM,
                            0,
                            &m_fmodMusic);

    m_fmodMusic->getLength(&m_uiSongLenght_ms, FMOD_TIMEUNIT_MS);
    m_fmodSystem->getChannel(1, &m_fmodChannel);

    //Set UI for this song
    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        m_FixtureMainTimingArr[i].setSongLength(m_uiSongLenght_ms);
    }
    m_iZoom = MAX_ZOOM_OUT_FROM_DEFAULT;
    applyZoom();
}

void Timing::setTimeUI()
{
    int seconds = int(m_uiCursor_ms) / int(1000);
    ui->lcdNumber->display(seconds);
}

void Timing::applyZoom()
{
    //TODO: Compute Boundaries
    //unsigned int songBigDiv = m_uiSongLenght_ms/m_iZoom

    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        //m_FixtureMainTimingArr[i]. TODO
    }
}

void Timing::zoomIn()
{
    //TODO: limit zoom
    m_iZoom ++;
    applyZoom();
}

void Timing::zoomOut()
{
    if(m_iZoom > 1 ){
        m_iZoom --;
        applyZoom();
    }
}

void Timing::on_pushButtonSoundtrack_clicked()
{
    //TODO: Open a window showing soundtrack statistics
}

void Timing::on_pushButtonAddCue_clicked()
{
    emit addCue();
}

void Timing::on_pushButtonSharpTransition_clicked()
{
    emit toggleSharp_Smooth();
}

void Timing::on_pushButtonDeleteCue_clicked()
{
    emit deleteCue();
}

void Timing::on_pushButtonPlay_clicked()
{
    //Import Mode
    if(m_fmodMusic == NULL){
        QString songPath = QFileDialog::getOpenFileName(this, "Load Song", QString(),
                                                    "Music(*.mp3)");
        if(!songPath.isEmpty()){
            loadSong(songPath);
            //Dit it work?
            if(m_fmodMusic != NULL){
                ui->pushButtonPlay->setText("Play");
            }
        }
    }
    else{
        //Play Mode
        if(!m_bIsPlaying){
            m_fmodSystem->playSound(m_fmodMusic, 0, false, &m_fmodChannel);
            setSongCurrentTime(m_uiCursor_ms);
            m_bIsPlaying = true;
            ui->pushButtonPlay->setText("Pause");

            //Callback
            connect(m_CallbackTimer, SIGNAL(timeout()), this, SLOT(update()));
        }

        //Pause Mode
        else{
            m_fmodSystem->playSound(m_fmodMusic, 0, true, &m_fmodChannel);
            m_bIsPlaying = false;
            ui->pushButtonPlay->setText("Play");

            //Pause Callback too
            disconnect(m_CallbackTimer, SIGNAL(timeout()), this, SLOT(update()));
        }
    }
}

void Timing::on_pushButtonRestart_clicked()
{
    setSongCurrentTime(0);
}

void Timing::on_pushButtonPreviousCue_clicked()
{
    //TODO
}

void Timing::on_pushButtonNextCue_clicked()
{
    //TODO
}

void Timing::on_pushButtonGoToEnd_clicked()
{
    setSongCurrentTime(m_uiSongLenght_ms-1);
}

void Timing::update()
{
    getSongCurrentTime();   //Update private member m_uiCursor_ms

    if(m_uiCursor_ms == m_uiSongLenght_ms){
        on_pushButtonPlay_clicked();
    }

    //Call Child
    int fixtAvailable = m_ptrLightsAvailable->getNumOfFixturesAvailable();
    for(int i = 0; i < fixtAvailable; i++)
    {
        //TODO
    }
}
