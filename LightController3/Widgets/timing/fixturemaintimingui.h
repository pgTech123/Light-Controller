#ifndef FIXTUREMAINTIMINGUI_H
#define FIXTUREMAINTIMINGUI_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QMenu>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "../faders.h"

#include <iostream>
using namespace std;

typedef struct{
    unsigned int timeID;
    bool sharp; //true = sharp, false = smooth
    //TODO: Fader data
}Cue;


namespace Ui {
class FixtureMainTimingUI;
}

class FixtureMainTimingUI : public QWidget
{
    Q_OBJECT

public:
    explicit FixtureMainTimingUI(QWidget *parent = 0);
    ~FixtureMainTimingUI();

    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);

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
    void releaseCueSelection();

    void setSongCursor(unsigned int cursor);

private slots:
    void updateUI();

private:
    void updateCueView();

signals:
    void zoomIn();
    void zoomOut();
    void releaseCuesSelection();
    void moveCursorTo(unsigned int);

private:
    Ui::FixtureMainTimingUI *ui;
    QMenu *m_btnMenu;
    QGraphicsScene *m_GraphScene;
    QGraphicsScene *m_GraphSceneCues;

    //Global
    int m_iFixtureId;
    Faders *m_FaderRef;

    //Pressed Key
    bool m_bCtrlPressed;
    bool m_bShiftPressed;
    bool m_bMousePressed;

    //Cues
    QList<Cue> m_ListCues;
    QList<int> m_ListSelectedCues;
    bool m_bImmunedCueRelease;

    //Viewport
    unsigned int m_uiViewMinTime;
    unsigned int m_uiViewMaxTime;
    int m_iTimeSeen;
    unsigned int m_uiCursor;

};

#endif // FIXTUREMAINTIMINGUI_H
