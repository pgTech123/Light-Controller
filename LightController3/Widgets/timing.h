#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include <QString>
#include "dockablewindow.h"

namespace Ui {
class Timing;
}

class Timing : public DockableWindow
{
    Q_OBJECT

public:
    explicit Timing(QWidget *parent = 0);
    ~Timing();

    bool loadShow(QString path);
    bool saveShow(bool saveAs = false);
    void setPathToScenes(QString path);
    void setPathToGroups(QString path);
    QString getPathToScenes();
    QString getPathToGroups();

    void reset();

private:
    Ui::Timing *ui;
};

#endif // TIMING_H
