#ifndef FADERS_H
#define FADERS_H

#include <QDockWidget>
#include <QCloseEvent>

namespace Ui {
class Faders;
}

class Faders : public QDockWidget
{
    Q_OBJECT

public:
    explicit Faders(QWidget *parent = 0);
    ~Faders();

    void closeEvent(QCloseEvent*);

signals:
    void hidden();
private:
    Ui::Faders *ui;
};

#endif // FADERS_H
