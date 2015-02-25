#ifndef SCENES_H
#define SCENES_H

#include <QDockWidget>
#include <QString>
#include "dockablewindow.h"

namespace Ui {
class Scenes;
}

class Scenes : public DockableWindow
{
    Q_OBJECT

public:
    explicit Scenes(QWidget *parent = 0);
    ~Scenes();

    bool loadScene(QString path);

private:
    Ui::Scenes *ui;
};

#endif // SCENES_H
