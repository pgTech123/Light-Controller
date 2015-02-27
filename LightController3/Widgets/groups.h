/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      group.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef GROUPS_H
#define GROUPS_H

#include "vector"
#include <QDockWidget>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include "dockablewindow.h"
#include "groupediting.h"
#include "lightsavailable.h"

using namespace std;

namespace Ui {
class Groups;
}

class Groups : public DockableWindow
{
    Q_OBJECT

public:
    explicit Groups(QWidget *parent = 0);
    ~Groups();

    bool loadGroups(QString path);
    bool saveGroups(bool saveAs = false);
    QString getPath();

    void reset();

    void setLightsAvailable(LightsAvailable *lightsAvailable);

private:
    void setFocusOnEditingGroup();

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();

    void on_save_groups_clicked();

    void newGroup(GroupContent group);
    void modifiedGroup(GroupContent group);

private:
    Ui::Groups *ui;

    QString m_pathToGroup;

    GroupEditing m_groupEditing;
    vector<GroupContent> m_groupsContent;
};

#endif // GROUPS_H
