#include "scenes.h"
#include "ui_scenes.h"

Scenes::Scenes(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Scenes)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);

    connect(&m_SceneEditingWindow, SIGNAL(CreateScene(SceneProperty)),
            this, SLOT(newScene(SceneProperty)));
    connect(&m_SceneEditingWindow, SIGNAL(ModifyScene(SceneProperty)),
            this, SLOT(modifiedScene(SceneProperty)));

    connect(ui->listWidgetScenes, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect(ui->listWidgetScenes,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(on_listWidgetScenes_itemClicked(QListWidgetItem*)));

    m_iCurrentScene = -1;
}

Scenes::~Scenes()
{
    delete ui;
}

bool Scenes::loadScenes(QString path)
{
    //TODO
    return true;
}

bool Scenes::saveScenes(bool saveAs)
{
    //TODO
    return true;
}

QString Scenes::getPath()
{
    //TODO
    return QString("");
}

void Scenes::reset()
{
    //TODO
}

void Scenes::setFaders(Faders *faders)
{
    m_ptrFaders = faders;
}

void Scenes::setFocusOnEditingGroup()
{
    m_SceneEditingWindow.setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           m_SceneEditingWindow.size(),
           qApp->desktop()->availableGeometry()
       ));
   m_SceneEditingWindow.show();
   m_SceneEditingWindow.activateWindow();
}

void Scenes::on_pushButtonNew_clicked()
{
    SceneProperty defaultScene;
    defaultScene.sceneName = "Scene";
    defaultScene.sceneProfile = ADDITIVE;

    m_SceneEditingWindow.setSceneProperty(defaultScene, true);
    setFocusOnEditingGroup();
}

void Scenes::on_pushButtonSave_clicked()
{
    if(m_iCurrentScene >= 0 && m_iCurrentScene < m_SceneVec.size()){
        m_SceneVec[m_iCurrentScene].lightStatus = m_ptrFaders->getLightsStatus();
    }
}

void Scenes::on_pushButtonDelete_clicked()
{
    int itemSelected = ui->listWidgetScenes->currentRow();
    if(itemSelected >= 0 && itemSelected < m_SceneVec.size()){
        int answer = QMessageBox::warning(this, "Warning",
                        tr("Are you sure you want to remove this scene?"),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
        if(answer == QMessageBox::Yes){
            m_SceneVec.erase(m_SceneVec.begin() + itemSelected);
            delete ui->listWidgetScenes->item(itemSelected);
        }
    }
    m_iCurrentScene = ui->listWidgetScenes->currentRow();
}

void Scenes::on_pushButtonApply_clicked()
{
    if(m_iCurrentScene >= 0 && m_iCurrentScene < m_SceneVec.size()){
        if(m_SceneVec[m_iCurrentScene].sceneProperties.sceneProfile == ADDITIVE){
            // Ignore faders with a value of 0
            for(int fixture = 0;
                fixture < m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus.size();
                fixture++)
            {
                for(int fader = 0;
                    fader < m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus[fixture].faderValue.size();
                    fader++)
                {
                    int value = m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus[fixture].faderValue[fader];
                    if(value != 0){
                        m_ptrFaders->setFader(fixture, fader, value);
                    }
                }
            }
        }
        else if(m_SceneVec[m_iCurrentScene].sceneProperties.sceneProfile == EXCLUSIVE){
            // Force to apply scene as it is recorded
            // Ignore faders with a value of 0
            for(int fixture = 0;
                fixture < m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus.size();
                fixture++)
            {
                for(int fader = 0;
                    fader < m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus[fixture].faderValue.size();
                    fader++)
                {
                    int value = m_SceneVec[m_iCurrentScene].lightStatus.fixtureStatus[fixture].faderValue[fader];
                    m_ptrFaders->setFader(fixture, fader, value);
                }
            }
        }
    }
}

void Scenes::on_save_scenes_clicked()
{
    if(!ui->save_scenes->isChecked()){
        int answer = QMessageBox::warning(this, "Warning",
                        tr("Are you sure you don't want to save the scenes for this project?"),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
        if(answer != QMessageBox::Yes){
            ui->save_scenes->setChecked(true);
        }
    }
}

void Scenes::on_listWidgetScenes_itemClicked(QListWidgetItem *item)
{
    m_iCurrentScene = ui->listWidgetScenes->row(item);
}

void Scenes::itemDoubleClicked(QListWidgetItem* item)
{
    int row = ui->listWidgetScenes->row(item);
    if(row >= 0 && row < m_SceneVec.size()){
        m_SceneEditingWindow.setSceneProperty(m_SceneVec[row].sceneProperties, false);
        setFocusOnEditingGroup();
    }
}

void Scenes::newScene(SceneProperty sceneProp)
{
    Scene sceneToAppend;
    sceneToAppend.sceneProperties = sceneProp;

    m_SceneVec.push_back(sceneToAppend);
    QListWidgetItem *item= new QListWidgetItem(sceneProp.sceneName);
    ui->listWidgetScenes->addItem(item);

    //Select it
    item->setSelected(true);
    on_listWidgetScenes_itemClicked(item);
}

void Scenes::modifiedScene(SceneProperty sceneProp)
{
    int itemSelected = ui->listWidgetScenes->currentRow();
    m_SceneVec[itemSelected].sceneProperties = sceneProp;
    ui->listWidgetScenes->item(itemSelected)->setText(sceneProp.sceneName);
}
