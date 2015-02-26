/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      lightsavailable.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef LIGHTSAVAILABLE_H
#define LIGHTSAVAILABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <QString>

using namespace std;

typedef struct{
    vector<QString> faderName;
}FaderNames;

class LightsAvailable
{
public:
    LightsAvailable(const char* path);

    int getNumOfFixturesAvailable();
    QString getFixtureName(int id);
    int getNumOfFadersForFixture(int id);
    QString getFaderName(int fixtureId, int faderId);

private:
    void readFile(const char* path);
    void addFixtureName(string name);
    void addFaderName(string name);

private:
    // Global
    int m_iFixturesAvailable;

    // Fixture
    vector<QString> m_QStrVecFixtureName;
    vector<int> m_iVecNumOfFaders;

    // Faders
    vector<FaderNames> m_faderName;
};

#endif // LIGHTSAVAILABLE_H
