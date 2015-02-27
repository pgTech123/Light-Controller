/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      groupediting.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef GROUPEDITING_H
#define GROUPEDITING_H

#include <QDialog>
#include <QList>
#include <QString>
#include "lightsavailable.h"

//DEBUG
#include <iostream>
using namespace std;

//TODO: disable other windows while open


typedef struct{
    QString groupName;
    QList<int> indexFixtures;
}GroupContent;

typedef enum{
    NEW, MODIFY
}EditingStatus;

namespace Ui {
class GroupEditing;
}

class GroupEditing : public QDialog
{
    Q_OBJECT

public:
    explicit GroupEditing(QWidget *parent = 0);
    ~GroupEditing();

    void newGroupContent();
    void setGroupContent(GroupContent groupContent);

    GroupContent getGroupContent();

    void setLightsAvailable(LightsAvailable *lightsAvailable);

private slots:
    void accept();

signals:
    void newGroup(GroupContent);
    void modifiedGroup(GroupContent);

private:
    Ui::GroupEditing *ui;
    LightsAvailable *m_ptrLightsAvailable;

    EditingStatus m_editingStatus;
    GroupContent m_currentGroup;
};

#endif // GROUPEDITING_H
