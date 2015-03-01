/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      singlefader.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/


#ifndef SINGLEFADER_H
#define SINGLEFADER_H

#include <QWidget>
#include <QString>
#include <QList>

namespace Ui {
class SingleFader;
}

typedef struct{
    int fixture;
    QList<int> faders;
}FadersToCall;

typedef struct{
    QList<FadersToCall> fixtures;
}FixturesToCall;

class SingleFader : public QWidget
{
    Q_OBJECT

public:
    explicit SingleFader(QWidget *parent = 0);
    ~SingleFader();

    void setName(QString name);
    void setFixtureAndFader(int fixture, int fader);
    void setFixturesAndFaders(FixturesToCall fixturesToCall);

public slots:
    void setValue(int value);
    void setValue(int fixture, int fader, int value);

private slots:
    void on_verticalSlider_valueChanged(int value);

signals:
    void valueChanged(int, int, int);

private:
    Ui::SingleFader *ui;

    FixturesToCall m_fixturesToCall;
};

#endif // SINGLEFADER_H
