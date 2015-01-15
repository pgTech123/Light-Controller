#ifndef DOCKABLEWINDOW_H
#define DOCKABLEWINDOW_H

#include <QDockWidget>
#include <QCloseEvent>

class DockableWindow : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockableWindow(QWidget *parent = 0);
    ~DockableWindow();
    void closeEvent(QCloseEvent*);

signals:
    void hidden();
};

#endif // DOCKABLEWINDOW_H
