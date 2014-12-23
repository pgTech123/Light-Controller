#ifndef ABOUTLIGHTCONTROLLER_H
#define ABOUTLIGHTCONTROLLER_H

#include <QWidget>
#include <QPixmap>
#include <QIcon>

#define PATH_TO_LOGO    "./../GVisionLogo.png"
#define ICON_PATH   "./../GVisionLogo.ico"

namespace Ui {
class AboutLightController;
}

class AboutLightController : public QWidget
{
    Q_OBJECT

public:
    explicit AboutLightController(QWidget *parent = 0);
    ~AboutLightController();

private:
    Ui::AboutLightController *ui;
};

#endif // ABOUTLIGHTCONTROLLER_H
