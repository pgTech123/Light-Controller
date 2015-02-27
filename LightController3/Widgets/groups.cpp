/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      group.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "groups.h"
#include "ui_groups.h"

Groups::Groups(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Groups)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);

    connect(&m_groupEditing, SIGNAL(newGroup(GroupContent)), this, SLOT(newGroup(GroupContent)));
    connect(&m_groupEditing, SIGNAL(modifiedGroup(GroupContent)), this, SLOT(modifiedGroup(GroupContent)));
}

Groups::~Groups()
{
    delete ui;
}

bool Groups::loadGroups(QString path)
{
    //TODO
    return true;
}

bool Groups::saveGroups(bool saveAs)
{
    if(!ui->save_groups->isChecked()){
        return true;
    }
    else{
        //TODO
        return true;
    }
}

QString Groups::getPath()
{
    return m_pathToGroup;
}

void Groups::reset()
{
    m_groupsContent.clear();
    ui->listWidgetGroups->clear();
}

void Groups::setLightsAvailable(LightsAvailable *lightsAvailable){
    m_groupEditing.setLightsAvailable(lightsAvailable);
}

void Groups::setFocusOnEditingGroup()
{
    m_groupEditing.setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           m_groupEditing.size(),
           qApp->desktop()->availableGeometry()
       ));
   m_groupEditing.show();
   m_groupEditing.activateWindow();
}

void Groups::on_pushButtonNew_clicked()
{
    m_groupEditing.newGroupContent();
    setFocusOnEditingGroup();
}

void Groups::on_pushButtonModify_clicked()
{
    if(ui->listWidgetGroups->currentRow() >= 0){
        m_groupEditing.setGroupContent(m_groupsContent[ui->listWidgetGroups->currentRow()]);
        setFocusOnEditingGroup();
    }
}

void Groups::on_pushButtonDelete_clicked()
{
    int itemSelected = ui->listWidgetGroups->currentRow();
    if(itemSelected >= 0){
        int answer = QMessageBox::warning(this, "Warning",
                        tr("Are you sure you want to remove this group?"),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
        if(answer == QMessageBox::Yes){
            m_groupsContent.erase(m_groupsContent.begin() + itemSelected);
            delete ui->listWidgetGroups->item(itemSelected);
        }
    }
}

void Groups::on_save_groups_clicked()
{
    if(!ui->save_groups->isChecked()){
        int answer = QMessageBox::warning(this, "Warning",
                        tr("Are you sure you don't want to save the groups for this project?"),
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::No);
        if(answer != QMessageBox::Yes){
            ui->save_groups->setChecked(true);
        }
    }
}

void Groups::newGroup(GroupContent group)
{
    m_groupsContent.push_back(group);
    QListWidgetItem *item= new QListWidgetItem(group.groupName);
    ui->listWidgetGroups->addItem(item);
}

void Groups::modifiedGroup(GroupContent group)
{
    int itemSelected = ui->listWidgetGroups->currentRow();
    m_groupsContent[itemSelected] = group;
    ui->listWidgetGroups->item(itemSelected)->setText(group.groupName);
}
