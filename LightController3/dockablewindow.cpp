#include "dockablewindow.h"

DockableWindow::DockableWindow(QWidget *parent) :
    QDockWidget(parent)
{
}

DockableWindow::~DockableWindow()
{
}

void DockableWindow::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}
