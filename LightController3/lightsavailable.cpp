/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      lightsavailable.cpp
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#include "lightsavailable.h"

LightsAvailable::LightsAvailable(const char* path)
{
    // Preset to Nothing available
    m_iFixturesAvailable = -1;

    readFile(path);
}

int LightsAvailable::getNumOfFixturesAvailable()
{
    return m_iFixturesAvailable;
}

QString LightsAvailable::getFixtureName(int id)
{
    if(id < m_iFixturesAvailable && id >= 0){
        return m_QStrVecFixtureName[id];
    }
    return QString("");
}

int LightsAvailable::getNumOfFadersForFixture(int id)
{
    if(id < m_iFixturesAvailable && id >= 0){
        return m_iVecNumOfFaders[id];
    }
    return -1;
}

QString LightsAvailable::getFaderName(int fixtureId, int faderId)
{
    if(fixtureId < m_iFixturesAvailable && fixtureId >= 0){
        if(faderId < m_iVecNumOfFaders[fixtureId] && faderId >=0){
            return m_faderName[fixtureId].faderName[faderId];
        }
    }
    return QString("");
}

void LightsAvailable::readFile(const char* path)
{
    ifstream file(path);
    if(file.is_open()){
        m_iFixturesAvailable = 0;
        string buf;
        while(getline(file, buf)){
            if(buf.empty()){
                //Skip this line
            }
            else if(buf.at(0) == '>'){
                buf.erase(0,1);
                addFixtureName(buf);
            }
            else{
                addFaderName(buf);
            }
        }
        file.close();
    }
}

void LightsAvailable::addFixtureName(string name)
{
    m_iFixturesAvailable ++;
    m_QStrVecFixtureName.push_back(QString(name.c_str()));
    m_iVecNumOfFaders.push_back(0);
    FaderNames fader;
    m_faderName.push_back(fader);
}

void LightsAvailable::addFaderName(string name)
{
    int current = m_iFixturesAvailable-1;
    m_iVecNumOfFaders[current]++;
    m_faderName[current].faderName.push_back(QString(name.c_str()));
}
