#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>
#include <QMenu>
#include <QString>
#include <QColor>
#include <QList>
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>

#include <stdlib.h>

//DEBUG
#include <iostream>
//END DEBUG

using namespace std;


typedef struct{
    unsigned int timeID;
    bool sharp; //true = sharp, false = smooth
    vector<bool> faderConcerned;
    vector<int> faderValue;
    //TODO: ITEM :redifine it to be clickable...
}Cue;


class Channel: public QWidget
{

    Q_OBJECT

public:
    Channel(QMenu *menu, QString name);

    QColor getChannelColor();
    bool isSelected();

    void selectCue(/*TODO*/);
    void releaseCue();
    void releaseCues(/*TODO*/);

    void addCue(unsigned int time);
    void toggleSharpnessOnSelectedCues();
    void deleteSelectedCues();

    void drawCuesBetween(QGraphicsScene *scene, unsigned int lowerTime, unsigned int higherTime);

public slots:
    void setVisible(bool visible);

private:
    void selectChannelColor();

private slots:
    void channelToggled();

private:
    //Button
    QAction *m_ActionChannelSelection;

    //Channel info
    QString m_channelName;
    QColor m_channelColor;
    QPen m_pen;
    QBrush m_brush;

};

#endif // CHANNEL_H
