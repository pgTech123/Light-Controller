#ifndef SCENES_H
#define SCENES_H

#include <QDockWidget>
#include <QString>
#include <QMessageBox>
#include "dockablewindow.h"

typedef struct{
    QString sceneName;
    //TODO: scene
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

private slots:
    void on_pushButtonNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();

    void on_save_scenes_clicked();

private:
    Ui::Scenes *ui;
};

#endif // SCENES_H
