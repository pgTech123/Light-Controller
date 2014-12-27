#ifndef GROUPS_H
#define GROUPS_H

#include <QDockWidget>
#include <QCloseEvent>

namespace Ui {
class Groups;
}

class Groups : public QDockWidget
{
    Q_OBJECT

public:
    explicit Groups(QWidget *parent = 0);
    ~Groups();
    void closeEvent(QCloseEvent*);

signals:
    void hidden();

private:
    Ui::Groups *ui;
};

#endif // GROUPS_H
