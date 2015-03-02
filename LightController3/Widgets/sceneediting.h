#ifndef SCENEEDITING_H
#define SCENEEDITING_H

#include <QDialog>
#include <QString>

typedef enum{
    ADDITIVE, EXCLUSIVE
}SceneProfile;

typedef struct{
    QString sceneName;
    SceneProfile sceneProfile;
}SceneProperty;

namespace Ui {
class SceneEditing;
}

class SceneEditing : public QDialog
{
    Q_OBJECT

public:
    explicit SceneEditing(QWidget *parent = 0);
    ~SceneEditing();

    void setSceneProperty(SceneProperty property, bool newScene = true);

signals:
    void CreateScene(SceneProperty);
    void ModifyScene(SceneProperty);

private slots:
    void accept();

private:
    Ui::SceneEditing *ui;
    bool m_NewScene;
};

#endif // SCENEEDITING_H
