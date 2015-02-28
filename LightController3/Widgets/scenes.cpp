#include "scenes.h"
#include "ui_scenes.h"

Scenes::Scenes(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Scenes)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);
}

Scenes::~Scenes()
{
    delete ui;
}

bool Scenes::loadScenes(QString path)
{
    return true;
}

bool Scenes::saveScenes(bool saveAs)
{
    return true;
}

QString Scenes::getPath()
{
    return QString("");
}

void Scenes::reset()
{

}

void Scenes::on_pushButtonNew_clicked()
{

}

void Scenes::on_pushButtonModify_clicked()
{

}

void Scenes::on_pushButtonDelete_clicked()
{

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
