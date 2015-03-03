#ifndef CUECURSOR_H
#define CUECURSOR_H

#include <QWidget>
#include <QMouseEvent>

class CueCursor : public QWidget
{
    Q_OBJECT
public:
    explicit CueCursor(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // CUECURSOR_H
