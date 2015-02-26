#ifndef GROUPS_H
#define GROUPS_H

#include <QDockWidget>
#include <QString>
#include "dockablewindow.h"
#include "groupediting.h"

//TODO: checkbox to be able to not save groups. Warning when uncheck

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

private:
    Ui::Groups *ui;
};

#endif // GROUPS_H
