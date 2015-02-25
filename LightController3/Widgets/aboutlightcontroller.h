/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      aboutlightcontroller.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef ABOUTLIGHTCONTROLLER_H
#define ABOUTLIGHTCONTROLLER_H

#include <QWidget>
#include <QPixmap>
#include <QIcon>

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
