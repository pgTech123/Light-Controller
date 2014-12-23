#ifndef FIXTURES_H
#define FIXTURES_H

#include <QDockWidget>
#include <QCloseEvent>

#define FIXTURE_INFO_PATH   ./../structure.txt

namespace Ui {
class Fixtures;
}

class Fixtures : public QDockWidget
{
    Q_OBJECT

public:
    explicit Fixtures(QWidget *parent = 0);
    ~Fixtures();

    void closeEvent(QCloseEvent*);

    void unselectAll();

private:
    void readStructureInfo();

signals:
    void hidden();

private:
    Ui::Fixtures *ui;
};

#endif // FIXTURES_H
