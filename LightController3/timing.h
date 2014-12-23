#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include <QCloseEvent>

namespace Ui {
class Timing;
}

class Timing : public QDockWidget
{
    Q_OBJECT

public:
    explicit Timing(QWidget *parent = 0);
    ~Timing();

    void closeEvent(QCloseEvent*);

signals:
    void hidden();

private:
    Ui::Timing *ui;
};

#endif // TIMING_H
