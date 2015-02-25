#ifndef GROUPS_H
#define GROUPS_H

#include <QDockWidget>
#include <QString>
#include "dockablewindow.h"

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

private:
    Ui::Groups *ui;
};

#endif // GROUPS_H
