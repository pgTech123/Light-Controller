#ifndef SCENES_H
#define SCENES_H

#include <vector>
#include <QDockWidget>
#include <QString>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDesktopWidget>
#include "dockablewindow.h"
#include "sceneediting.h"
#include "faders.h"

using namespace std;

typedef struct{
    SceneProperty sceneProperties;
    LightsStatus lightStatus;
}Scene;

namespace Ui {
class Scenes;
}

class Scenes : public DockableWindow
{
    Q_OBJECT

public:
    explicit Scenes(QWidget *parent = 0);
    ~Scenes();

    bool loadScenes(QString path);
    bool saveScenes(bool saveAs = false);
    QString getPath();
    void reset();

    void setFaders(Faders *faders);

    void setFocusOnEditingGroup();

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonDelete_clicked();

    void on_pushButtonApply_clicked();

    void on_save_scenes_clicked();

    void on_listWidgetScenes_itemClicked(QListWidgetItem* item);

    void itemDoubleClicked(QListWidgetItem* item);

    void newScene(SceneProperty sceneProp);
    void modifiedScene(SceneProperty sceneProp);

private:
    Ui::Scenes *ui;

    Faders *m_ptrFaders;

    int m_iCurrentScene;

    SceneEditing m_SceneEditingWindow;
    vector<Scene> m_SceneVec;
};

#endif // SCENES_H
