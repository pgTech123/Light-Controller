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

namespace Ui {
class SingleFader;
}

class SingleFader : public QWidget
{
    Q_OBJECT

public:
    explicit SingleFader(QWidget *parent = 0);
    ~SingleFader();

public slots:
    void setValue(int value);

private slots:
    void on_verticalSlider_valueChanged(int value);

signals:
    void valueChanged(int);

private:
    Ui::SingleFader *ui;
};

#endif // SINGLEFADER_H
