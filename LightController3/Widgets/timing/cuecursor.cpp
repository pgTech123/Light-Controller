#include "cuecursor.h"

CueCursor::CueCursor(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedWidth(7);
    this->setFixedHeight(7);
}

void CueCursor::mousePressEvent(QMouseEvent *event)
{
    //TODO: change color
}
