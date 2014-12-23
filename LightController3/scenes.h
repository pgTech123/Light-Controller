#ifndef SCENES_H
#define SCENES_H

#include <QDockWidget>
#include <QCloseEvent>

namespace Ui {
class Scenes;
}

class Scenes : public QDockWidget
{
    Q_OBJECT

public:
    explicit Scenes(QWidget *parent = 0);
    ~Scenes();
    void closeEvent(QCloseEvent*);

signals:
    void hidden();

private:
    Ui::Scenes *ui;
};

#endif // SCENES_H
