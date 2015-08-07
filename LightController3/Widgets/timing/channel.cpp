#include "channel.h"

Channel::Channel(QMenu *menu, QString name)
{
    m_channelName = name;
    m_ActionChannelSelection = menu->addAction(m_channelName);
    m_ActionChannelSelection->setCheckable(true);
    m_ActionChannelSelection->setChecked(true);

    connect(m_ActionChannelSelection, SIGNAL(changed()), this, SLOT(channelToggled()));

    selectChannelColor();
}

QColor Channel::getChannelColor()
{
    return m_channelColor;
}

bool Channel::isSelected()
{
    return m_ActionChannelSelection->isChecked();
}

void Channel::selectCue(/*TODO*/)
{

}

void Channel::releaseCue(/*TODO*/)
{

}

void Channel::releaseCues()
{

}

void Channel::addCue(unsigned int time)
{
    //TODO
}


void Channel::toggleSharpnessOnSelectedCues()
{

}

void Channel::deleteSelectedCues()
{

}

void Channel::drawCuesBetween(QGraphicsScene *scene, unsigned int lowerTime, unsigned int higherTime)
{


    scene->addRect(50, 100, 10, 10, m_pen, m_brush);
}

void Channel::setVisible(bool visible)
{
    m_ActionChannelSelection->setChecked(visible);
}

void Channel::selectChannelColor()
{
    if(m_channelName == "red" || m_channelName == "Red" || m_channelName == "RED"){
        m_channelColor = QColor(255,0,0);
        m_brush.setStyle(Qt::Dense3Pattern);
        m_brush.setColor(m_channelColor);
        m_pen.setColor(m_channelColor);
    }
    else if(m_channelName == "green" || m_channelName == "Green" || m_channelName == "GREEN"){
        m_channelColor = QColor(0,255,0);
        m_brush.setStyle(Qt::Dense4Pattern);
        m_brush.setColor(m_channelColor);
        m_pen.setColor(m_channelColor);
    }
    else if(m_channelName == "blue" || m_channelName == "Blue" || m_channelName == "BLUE"){
        m_channelColor = QColor(0,0,255);
        m_brush.setStyle(Qt::Dense5Pattern);
        m_brush.setColor(m_channelColor);
        m_pen.setColor(m_channelColor);
    }
    else if(m_channelName == "pos" || m_channelName == "Pos" || m_channelName == "POS"){
        m_channelColor = QColor(0,0,0);
        m_brush.setStyle(Qt::Dense6Pattern);
        m_brush.setColor(m_channelColor);
        m_pen.setColor(m_channelColor);
    }
    else{
        int red = rand() % 255;
        int green = rand() % 255;
        int blue = rand() % 255;
        m_channelColor = QColor(red, green, blue);
        m_brush.setStyle(Qt::Dense7Pattern);
        m_brush.setColor(m_channelColor);
        m_pen.setColor(m_channelColor);
    }
}

void Channel::channelToggled()
{
    //TODO: Call a redraw on the parent fixture
}
