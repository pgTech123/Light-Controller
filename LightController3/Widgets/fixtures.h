#ifndef FIXTURES_H
#define FIXTURES_H

#include <QDockWidget>
#include "dockablewindow.h"

#define FIXTURE_INFO_PATH   ./../structure.txt

namespace Ui {
class Fixtures;
}

class Fixtures : public DockableWindow
{
    Q_OBJECT

public:
    explicit Fixtures(QWidget *parent = 0);
    ~Fixtures();

    void unselectAll();

private:
    void readStructureInfo();

private:
    Ui::Fixtures *ui;
};

#endif // FIXTURES_H
