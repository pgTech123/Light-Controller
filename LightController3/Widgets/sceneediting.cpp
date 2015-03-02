#include "sceneediting.h"
#include "ui_sceneediting.h"

SceneEditing::SceneEditing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneEditing)
{
    ui->setupUi(this);
    this->setLayout(ui->gridLayout);
    this->setFixedWidth(325);
    this->setFixedHeight(100);

    //Force focus and freeze other windows
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setModal(true);
}

SceneEditing::~SceneEditing()
{
    delete ui;
}

void SceneEditing::setSceneProperty(SceneProperty property, bool newScene)
{
    m_NewScene = newScene;
    ui->lineEdit->setText(property.sceneName);
    if(property.sceneProfile == ADDITIVE){
        ui->radioButtonAdditive->setChecked(true);
    }
    else if(property.sceneProfile == EXCLUSIVE){
        ui->radioButtonExclusive->setChecked(true);
    }
}

void SceneEditing::accept()
{
    SceneProperty property;
    property.sceneName = ui->lineEdit->text();
    if(ui->radioButtonAdditive->isChecked()){
        property.sceneProfile = ADDITIVE;
    }
    else if(ui->radioButtonExclusive->isChecked()){
        property.sceneProfile = EXCLUSIVE;
    }

    if(m_NewScene){
        emit CreateScene(property);
    }
    else{
        emit ModifyScene(property);
    }
    QDialog::accept();
}
