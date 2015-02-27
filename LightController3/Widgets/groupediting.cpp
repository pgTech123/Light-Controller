/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      groupediting.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "groupediting.h"
#include "ui_groupediting.h"

GroupEditing::GroupEditing(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupEditing)
{
    ui->setupUi(this);

    this->setLayout(ui->verticalLayout_2);
    this->setFixedWidth(350);

    //Force focus and freeze other windows
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setModal(true);
}

GroupEditing::~GroupEditing()
{
    delete ui;
}

void GroupEditing::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;
}

void GroupEditing::newGroupContent()
{
    GroupContent group;
    m_currentGroup = group;
    m_editingStatus = NEW;

    ui->lineEdit->setText("New Group");
    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        //TODO: create checkbox and add it to layout
    }
}

void GroupEditing::setGroupContent(GroupContent groupContent)
{
    m_currentGroup = groupContent;
    m_editingStatus = MODIFY;

    ui->lineEdit->setText(groupContent.groupName);
    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        //TODO: create checkbox, check those who are selected and add it to layout
    }
}

GroupContent GroupEditing::getGroupContent()
{
    return m_currentGroup;
}

void GroupEditing::accept()
{
    m_currentGroup.groupName = ui->lineEdit->text();
    if(m_editingStatus == NEW){
        emit newGroup(m_currentGroup);
    }
    else{
        emit modifiedGroup(m_currentGroup);
    }
    QDialog::accept();
}
