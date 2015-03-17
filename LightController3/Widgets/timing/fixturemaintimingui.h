#ifndef FIXTUREMAINTIMINGUI_H
#define FIXTUREMAINTIMINGUI_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QMenu>
#include "../faders.h"

namespace Ui {
class FixtureMainTimingUI;
}

class FixtureMainTimingUI : public QWidget
{
    Q_OBJECT

public:
    explicit FixtureMainTimingUI(QWidget *parent = 0);
    ~FixtureMainTimingUI();

    void setFixtureName(QString name);
    void addFaderNames(QList<QString> name);
    void setFixtureID(int fixtureID);
    void setFaders(Faders *faders);
    void setSongLength(unsigned int length);
    void setZoomBoundary(unsigned int min, unsigned int max);

public slots:
    void addCue();
    void toggleSharp_Smooth();
    void deleteCue();

    void setSongCursor(unsigned int cursor);

private slots:

signals:
    void zoomIn();
    void zoomOut();

private:
    Ui::FixtureMainTimingUI *ui;
    QMenu *m_btnMenu;

    //Viewport
    unsigned int m_uiViewMinTime;
    unsigned int m_uiViewMaxTime;

};

#endif // FIXTUREMAINTIMINGUI_H
