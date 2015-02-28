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

    m_CheckBoxArray = NULL;

    this->setLayout(ui->verticalLayout_2);
    this->setFixedWidth(250);

    //Force focus and freeze other windows
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setModal(true);
}

GroupEditing::~GroupEditing()
{
    delete ui;
    if(m_CheckBoxArray != NULL){
        delete[] m_CheckBoxArray;
    }
}

void GroupEditing::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;

    m_CheckBoxArray = new QCheckBox[m_ptrLightsAvailable->getNumOfFixturesAvailable()];

    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        m_CheckBoxArray[i].setText(m_ptrLightsAvailable->getFixtureName(i));
        ui->verticalLayout->addWidget(&m_CheckBoxArray[i]);
    }
}

void GroupEditing::newGroupContent()
{
    GroupContent group;
    m_currentGroup = group;
    m_editingStatus = NEW;

    ui->lineEdit->setText("New Group");

    uncheckAll();
}

void GroupEditing::setGroupContent(GroupContent groupContent)
{
    m_currentGroup = groupContent;
    m_editingStatus = MODIFY;

    ui->lineEdit->setText(groupContent.groupName);

    // Check fixtures that are in the group
    uncheckAll();
    for(int i = 0; i < m_currentGroup.indexFixtures.size(); i++){
        m_CheckBoxArray[m_currentGroup.indexFixtures.at(i)].setChecked(true);
    }
}

GroupContent GroupEditing::getGroupContent()
{
    return m_currentGroup;
}

void GroupEditing::uncheckAll()
{
    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        m_CheckBoxArray[i].setChecked(false);
    }
}

void GroupEditing::accept()
{
    m_currentGroup.groupName = ui->lineEdit->text();

    //Update Fixtures in Group
    m_currentGroup.indexFixtures.clear();
    for(int i = 0; i < m_ptrLightsAvailable->getNumOfFixturesAvailable(); i++){
        if(m_CheckBoxArray[i].isChecked()){
            m_currentGroup.indexFixtures.append(i);
        }
    }

    if(m_editingStatus == NEW){
        emit newGroup(m_currentGroup);
    }
    else{
        emit modifiedGroup(m_currentGroup);
    }
    QDialog::accept();
}
